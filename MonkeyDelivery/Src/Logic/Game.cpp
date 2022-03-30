#include "Game.h"
#include "../Control/UI/ElementsUI/Brightness.h"
void Game::loadSpriteSheets()
{
    string filename = "../Images/config/resources.json";

    std::unique_ptr<JSONValue> jValueRoot(JSON::ParseFromFile(filename));

    if (jValueRoot == nullptr || !jValueRoot->IsObject()) {
        throw "Something went wrong while load/parsing '" + filename + "'";
    }

    JSONObject root = jValueRoot->AsObject();
    JSONValue* jValue = nullptr;

    // load tilesets
    jValue = root["tilesets"];
    if (jValue != nullptr) {
        if (jValue->IsArray()) {
            for (auto& v : jValue->AsArray()) {
                if (v->IsObject()) {
                    JSONObject vObj = v->AsObject();
                    std::string key = vObj["id"]->AsString();
                    std::string file = vObj["file"]->AsString();
                    auto a = new Texture(renderer, file);
                    tilesets_.emplace(std::make_pair(key, a));
                }
                else {
                    throw "'tilesets' array in '" + filename
                        + "' includes and invalid value";
                }
            }
        }
        else {
            throw "'tilesets' is not an array";
        }
    }
}

void Game::setCamera()
{
    Vector2D<float> newPos = mCamera_->getCameraPosition();
    newPos.setX((player_->getX() + player_->getWidth() / 2)); // -mCamera_->getWidth() / 2;
    newPos.setY((player_->getY() + player_->getHeight() / 2)); // -mCamera_->getHeight() / 2;

    // para evitar que se salga del mapa
    int bgWidth = mapInfo.tile_width * mapInfo.cols;
    int bgHeight = mapInfo.tile_height * mapInfo.rows;
    if (newPos.getX() < 0) {
        newPos.setX(0);
    }
    if (newPos.getY() < 0) {
        newPos.setY(0);
    }
    if (newPos.getX() > bgWidth) {
        newPos.setX(bgWidth);
    }
    if (newPos.getY() > bgHeight) {
        newPos.setY(bgHeight);
    }

    // Movemos la cámara a la nueva pos
    mCamera_->Move(newPos);
}

Game::Game(string n, int w, int h) : name(n), width(w), height(h), doExit(false), mCamera_(nullptr), mapOpened(false)
{
    SDLUtils::init("Monkey Delivery", 1800, 1000,
        "../Images/config/resources.json");

    setRenderer(sdlutils().renderer());

    font_ = new Font("../Images/TheMoon.ttf", 50);
}

Game::~Game() {
    //usar iteradores
    for (auto gO : gameObjects_)
    {
        delete gO;
    }
    for (auto enemy : enemyContainer_)
        delete enemy;

    for (auto col : collisions_)
        delete col;

    gameObjects_.clear();
    enemyContainer_.clear();
    cout << "[DEBUG] deleting game" << endl;
    delete player_;
    delete textureContainer_;
    delete font_;
    delete info;
    //delete missionsPanel_; //solo poner si no va en el vector de gameobjects
    delete dialogueBox_;
    delete iE_;
    delete animationManager;
    delete shop_;
    delete mCamera_;
    for (auto a : tilesets_) {
        a.second->free();
        delete a.second;
    }
    for (auto x : savedStates) {
        delete x;
    }
    SDL_SetWindowBrightness(sdlutils().window(), 1);
}

string Game::getGameName() {
    return name;
}

void Game::add(GameObject* gameObject) {//a�adir gO al vector
    gameObjects_.push_back(gameObject);
}

void Game::start()
{
    //loadSpriteSheets();
    mapInfo.path = ".\\Src\\TilemapSrc\\MainMap.tmx";
    loadMap(mapInfo.path);

    // Cámara:
    mCamera_ = new Camera(this, CAMINITPOSITION_, getWindowWidth() * MAPSCALE_, getWindowHeight() * MAPSCALE_); // /2 -> es la proporción de tamaño del mapa. Valor más pequeño hace que el mapa se vea + pequeño y viceversa
    // dónde spawnea -> qué se ve del mapa
    srcRect_ = mCamera_->renderRect();
    // srcRect_ = {(int)camPos.getX(), (int)camPos.getY(), (int)mCamera_->getWidth(), (int)mCamera_->getHeight()}; // == lo que devuelve el renderRect
    animationManager = new AnimationManager(this);
    player_ = new Player(this, animationManager); //Creacion del jugador

    missionsPanel_ = new MissionsPanel(this);
    add(missionsPanel_);

    add(new IntectuableShop(this, 300, 40));
    shop_ = new Shop(player_, this);

    add(new InteractuableChest(this, 400, 400, 100, 100, 0));

    add(new TutorialBook(this, 500, 500, 100, 75));

    enemiesCreation();//creacion de enemigos

    dialogueBox_ = new DialogueBox(this);
    // dialogueBox_->changeText("DialogueBox1");
    // dialogueBox_->show();

    info = new UI_Info(this);
    auto* x = new Bed(this);
    x->setPosition(670, 760);
    add(x);
}

void Game::update()
{
    player_->update();
   
    for (auto c : collisions_) {
        if (c->getPosition().getX() && c->collide(player_->getCollider())) {
            //cout << "player colliding\n";
        }
    }

     for (auto gO : gameObjects_)
        gO->update();


    for (auto enemy : enemyContainer_)
        enemy->update();

}

void Game::setUserExit() {
    doExit = true;
}

bool Game::isUserExit() {
    return doExit;
}

//Normal draw for entities(no Tiles)
void Game::draw()
{
    // Dibujado del mapa
    int bgWidth = mapInfo.tile_width * mapInfo.cols;
    int bgHeight = mapInfo.tile_height * mapInfo.rows;
    SDL_Rect dst = { 0, 0, getWindowWidth(), getWindowHeight() }; // Se dibuja en la totalidad de la pantalla (modificar si quisieramos dejar un borde de UI por ejemplo)
    srcRect_ = mCamera_->renderRect();
    SDL_RenderCopy(renderer, background_, &srcRect_, &dst); // srcRect es la parte de la textura (background) que se va a ver

    /*auto a = SDL_GetWindowSurface(window_);
    auto tex = SDL_CreateTextureFromSurface(renderer, a);
    background_ = SDL_CreateTextureFromSurface(renderer, a);
    SDL_RenderCopy(renderer, background_, NULL, &dst);*/

  
    for (auto gO : gameObjects_)
        gO->draw();

    
    for (auto enemy : enemyContainer_)
        enemy->draw();
    

    info->draw();

    missionsPanel_->draw();

    dialogueBox_->draw();

    player_->draw();
}

Point2D<int> Game::getOrigin() {
    return { int(-(player_->getX() - player_->getWidth())), 0 };
}

int Game::getWindowWidth() {
    return width;
}

int Game::getWindowHeight() {
    return height;
}

void Game::useInventory(int slot)
{
    player_->useObject(slot);
}

void Game::setRenderer(SDL_Renderer* _renderer) {
    renderer = _renderer;
}

void Game::loadTextures() {
    if (renderer == nullptr)
        throw string("Renderer is null");

    textureContainer_ = new TextureContainer(renderer);
}

Texture* Game::getTexture(TextureName name) {
    return textureContainer_->getTexture(name);
}

SDL_Renderer* Game::getRenderer() {
    return renderer;
}

void Game::renderText(string text, int x, int y, SDL_Color color)
{
    font_->render(renderer, text.c_str(), x, y, color);
}

void Game::renderText(vector<string> text, int x, int y, int incX, int incY, SDL_Color color)
{
    for (int i = 0; i < text.size(); ++i) {
        font_->render(renderer, text[i].c_str(), x, y, color);
        x += incX;
        y += incY;
    }
}

//economy
//modifica el dinero del jugador y devulve bool de confirmaci�n en caso de compra
//actua como enlace al m�todo del jugador
bool Game::changeMoneyPlayer(int money)
{
    return player_->moneyChange(money);
}

//adri y simona: colisiones
vector<GameObject*> Game::getCollisions(SDL_Rect rect)
{
    vector<GameObject*>interactEnt;

    // for que recorre el vector de gameobjects
    for (int i = 0; i < gameObjects_.size(); i++)
    {
        // gameObjects_[i]->isInteractive() quitar�a esto del if
        if (gameObjects_[i]->collide(rect)) {
            interactEnt.push_back(gameObjects_[i]);
        }
    }

    return interactEnt;
}

// devuelve la iE 
InteractiveEntity* Game::getiE()
{
    return iE_;
}
void Game::addEnemies(Enemy* enemy)
{
    enemyContainer_.push_back(enemy);
}
void Game::enemiesCreation()
{
     //zona derecha desde el inicio (pradera)
    addEnemies(new Plant(this, 60, Point2D<int>(1100, 200), animationManager));
    addEnemies(new Plant(this, 60, Point2D<int>(1200, 350), animationManager));
    addEnemies(new Plant(this, 60, Point2D<int>(1600, 450), animationManager));
    addEnemies(new Plant(this, 60, Point2D<int>(1700, 600), animationManager));

    //zona inferior izquierda desde el inicio(camino junto al mar)
    addEnemies(new Cat(this, 50, Point2D<int>(-100, 1300), animationManager));
    addEnemies(new Cat(this, 50, Point2D<int>(-200, 1100), animationManager));

    //zona inferior izquierda desde el inicio(cruce)
    addEnemies(new Scorpion(this, 80, Point2D<int>(-300, 1650), animationManager));
    addEnemies(new Scorpion(this, 80, Point2D<int>(-500, 1850), animationManager));

    //zona inferior izquierda desde el inicio(ante zona al puente isla del sur)
    addEnemies(new Cat(this, 50, Point2D<int>(-1000, 2300), animationManager));
    addEnemies(new Cat(this, 50, Point2D<int>(-250, 2450), animationManager));
    addEnemies(new Scorpion(this, 80, Point2D<int>(-550, 2500), animationManager));

    //zona inferior desde el inicio(bosque)
    addEnemies(new Bat(this, 20, Point2D<int>(450, 1500), 7, animationManager));
    addEnemies(new Bat(this, 20, Point2D<int>(800, 1800), 7, animationManager));
    addEnemies(new Bat(this, 20, Point2D<int>(1300, 2100), 7, animationManager));
    addEnemies(new Bat(this, 20, Point2D<int>(2250, 2000), 7, animationManager));

    addEnemies(new Bull(this, 70, Point2D<int>(1100, 200), animationManager));
}

void Game::scare(double scariness)
{
    player_->getScared(scariness);
}

void Game::interactDialogue()
{
    dialogueBox_->interact();
}


//TILEMAP
void Game::loadMap(string const& filename)
{
    // Se carga la información del .tmx
    mapInfo.tile_map = new tmx::Map();
    mapInfo.tile_map->load(filename);

    // tamaño del mapa
    auto map_dimensions = mapInfo.tile_map->getTileCount();
    mapInfo.rows = map_dimensions.y;
    mapInfo.cols = map_dimensions.x;

    // tamaño de los tiles
    auto tilesize = mapInfo.tile_map->getTileSize();
    mapInfo.tile_width = tilesize.x;
    mapInfo.tile_height = tilesize.y;

    // convertir a textura
    auto rend = renderer;
    int bgWidth = mapInfo.tile_width * mapInfo.cols;
    int bgHeight = mapInfo.tile_height * mapInfo.rows;
    //SDL_Texture* background_ = SDL_CreateTexture(rend,
    background_ = SDL_CreateTexture(rend,

        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        bgWidth,
        bgHeight
    );
    SDL_RenderClear(renderer);
    SDL_SetTextureBlendMode(background_, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, background_);


    //Establecemos los bordes de la camara con respecto al tamaño del tilemap
        //Camera::mainCamera->setBounds(0, 0, mapInfo.cols * mapInfo.tile_width, mapInfo.rows * mapInfo.tile_height);

    //Cargamos y almacenamos los tilesets utilizados por el tilemap
    // (el mapa utiliza el �ndice [gid] del primer tile cargado del tileset como clave)
    // (para poder cargar los tilesets del archivo .tmx, les ponemos de nombre 
    // el nombre del archivo sin extension en el .json) 
    auto& mapTilesets = mapInfo.tile_map->getTilesets();
    for (auto& tileset : mapTilesets) {
        string name = tileset.getName();
        Texture* texture = sdlutils().tilesets().find(name)->second;
        //Texture* texture = tilesets_.find(name)->second;;
        mapInfo.tilesets.insert(pair<uint, Texture*>(tileset.getFirstGID(), texture));
    }
    // recorremos cada una de las capas (de momento solo las de tiles) del mapa
    auto& map_layers = mapInfo.tile_map->getLayers();
    for (auto& layer : map_layers) {
        // aqui comprobamos que sea la capa de tiles
        if (layer->getType() == tmx::Layer::Type::Tile) {
            // cargamos la capa
            tmx::TileLayer* tile_layer = dynamic_cast<tmx::TileLayer*>(layer.get());

            // obtenemos sus tiles
            auto& layer_tiles = tile_layer->getTiles();

            // recorremos todos los tiles para obtener su informacion
            for (auto y = 0; y < mapInfo.rows; ++y) {
                for (auto x = 0; x < mapInfo.cols; ++x) {
                    // obtenemos el indice relativo del tile en el mapa de tiles
                    auto tile_index = x + (y * mapInfo.cols);

                    // con dicho indice obtenemos el indice del tile dentro de su tileset
                    auto cur_gid = layer_tiles[tile_index].ID;


                    // si es 0 esta vacio asi que continuamos a la siguiente iteracion
                    if (cur_gid == 0)
                        continue;

                    // guardamos el tileset que utiliza este tile (nos quedamos con el tileset cuyo gid sea
                    // el mas cercano, y a la vez menor, al gid del tile)
                    auto tset_gid = -1, tsx_file = 0;;
                    for (auto& ts : mapInfo.tilesets) {
                        if (ts.first <= cur_gid) {
                            tset_gid = ts.first;
                            tsx_file++;
                        }
                        else
                            break;
                    }

                    // si no hay tileset v�lido, continuamos a la siguiente iteracion
                    if (tset_gid == -1)
                        continue;

                    // normalizamos el �ndice
                    cur_gid -= tset_gid;

                    // calculamos dimensiones del tileset
                    auto ts_width = 0;
                    auto ts_height = 0;
                    SDL_QueryTexture(mapInfo.tilesets[tset_gid]->getTexture(),
                        NULL, NULL, &ts_width, &ts_height);

                    // calculamos el area del tileset que corresponde al dibujo del tile
                    auto region_x = (cur_gid % (ts_width / mapInfo.tile_width)) * mapInfo.tile_width;
                    auto region_y = (cur_gid / (ts_width / mapInfo.tile_width)) * mapInfo.tile_height;

                    // calculamos la posicion del tile
                    auto x_pos = x * mapInfo.tile_width;
                    auto y_pos = y * mapInfo.tile_height;


                    //bool is_wall = false; // Booleano de control
                    //// Acceso a las propiedades de una tile dentro de un tileset (.tsx)
                    //vector<tmx::Property> tile_props = mapInfo.tile_map.getTilesets()[tsx_file - 1].getTiles()[cur_gid].properties;
                    //if (tile_props.size() > 0) {
                    //	// Lo separo aqui por si en algun futuro creamos m�s propiedades, realmente habria que hacer una busqueda
                    //	// de la propiedad y si esta en el vector usarla acorde
                    //	if (tile_props[0].getName() == "wall")
                    //		is_wall = tile_props[0].getBoolValue();
                    //}

                    // metemos el tile
                    auto tileTex = mapInfo.tilesets[tset_gid];

                    SDL_Rect src;
                    src.x = region_x; src.y = region_y;
                    src.w = mapInfo.tile_width;
                    src.h = mapInfo.tile_height;

                    SDL_Rect dest;
                    dest.x = x_pos;
                    dest.y = y_pos;
                    dest.w = src.w;
                    dest.h = src.h;

                    int tileRot = layer_tiles[tile_index].flipFlags;
                    float rotCorrection = 45;
                    SDL_RendererFlip tileFlip = SDL_FLIP_NONE;
                    //switch (tileRot)
                    //{
                    //default:break;
                    //case 2:  rotCorrection = 180; break;
                    //case 4:  tileFlip = SDL_FLIP_HORIZONTAL; rotCorrection = 45; break;
                    //case 6:  rotCorrection = 225; break;
                    //case 8:  tileFlip = SDL_FLIP_HORIZONTAL; rotCorrection = 90; break;
                    //case 10:  tileFlip = SDL_FLIP_HORIZONTAL; rotCorrection = 90; break;
                    //case 12:  rotCorrection = 45; break;
                    //case 14:  rotCorrection = 225; tileFlip = SDL_FLIP_HORIZONTAL; tileFlip = SDL_FLIP_VERTICAL; break;
                    //    /*case 12:  tileFlip = SDL_FLIP_HORIZONTAL; rotCorrection = 90; break;
                    //    case 14:  tileFlip = SDL_FLIP_HORIZONTAL; rotCorrection = 90; break;*/
                    //    //case 14:   rotCorrection = 40; break;
                    //}

                    //Multiplicamos por 45 porque esta multiplicado por factor de 45 (lo que devuelve rot)
                    mapInfo.tilesets[tset_gid]->render(src, dest, tileRot * rotCorrection, nullptr, tileFlip);

                }
            }
        }

        if (layer->getType() == tmx::Layer::Type::Object) {
            tmx::ObjectGroup* object_layer = dynamic_cast<tmx::ObjectGroup*>(layer.get());

            auto& objs = object_layer->getObjects();

            for (auto obj : objs) {
                auto rect = obj.getAABB();

             //   if (obj.getName() == "collision") 
                    auto a = new ColliderTile(this, Vector2D<double>(rect.left, rect.top), rect.width, rect.height );
                    collisions_.push_back(a);
                
            }
        }
    }

    SDL_SetRenderTarget(renderer, nullptr);
}

void Game::aPlayerPos(float x, float y)
{
    //obtenemos la posicion actual de la camara
    Vector2D<float> current = mCamera_->getCameraPosition();

    int bgWidth = mapInfo.tile_width * mapInfo.cols;
    int bgHeight = mapInfo.tile_height * mapInfo.rows;
    //comprobamo si esta enalguno de los limites y si va a sobrepasar este, reducimos el desplazamiento a 0
    if ((x > -10 && current.getX() >= bgWidth) || (x < 0 && current.getX() <= 0))
        x = 0;
    if ((y > 0 && current.getY() >= bgHeight) || (y < 0 && current.getY() <= 0))
        y = 0;
    //aplicamos la nueva posicion a la camara
    mCamera_->setPos(current + Vector2D<float>(x, y));

    //para todos los gameobjects ajustamos su posicion respecto al jugador
    for (auto e : gameObjects_)
    {

        Point2D<double> newPos = e->getPosition() - (Point2D<double>(x, y) / MAPSCALE_);
        e->setPosition(newPos.getX(), newPos.getY());
    }

    for (auto e : enemyContainer_)
    {
        Point2D<double> move = Point2D<double>(x, y);

        Point2D<double> newPos = e->getPosition() - move / MAPSCALE_;
        e->setPosition(newPos.getX(), newPos.getY());
        e->changeOffset(move / -MAPSCALE_);
    }
}