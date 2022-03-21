#include "Game.h"

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

Game::Game(string n, int w, int h) : name(n), width(w), height(h), doExit(false)
{    
    font_ = new Font("../Images/TheMoon.ttf", 50);
    animationManager = new AnimationManager(this);
}

Game::~Game() {
    //usar iteradores
    for (auto gO : gameObjects_)
    {
        delete gO;
    }
    for (auto enemy : enemyContainer_)
        delete enemy;

    gameObjects_.clear();
    enemyContainer_.clear();
    cout << "[DEBUG] deleting game" << endl;
    delete player_;
    delete textureContainer_;
    delete font_;
    delete info;  
    //delete missionsPanel_; solo poner si no va en el vector de gameobjects
    delete dialogueBox_;
    delete iE_;
    delete animationManager;
    delete savedState;
    delete shop_;
}

string Game::getGameName() {
    return name;
}

void Game::add(GameObject* gameObject) {//a�adir gO al vector
    gameObjects_.push_back(gameObject);
}

void Game::start()
{
    loadSpriteSheets();
    mapInfo.path = ".\\Src\\TilemapSrc\\MainMap.tmx";
    loadMap(mapInfo.path);

    animationManager = new AnimationManager(this);
   
    player_ = new Player(this,animationManager); //Creacion del jugador
    //iE_ = new InteractiveEntity(this, tucanTexture, 500, 80);
    //add(iE_);

    missionsPanel_ = new MissionsPanel(this);
    add(missionsPanel_); 
    add (new IntectuableShop(this, 200, 200));
    enemiesCreation();//creacion de enemigos
    

    //missions_ = new MissionManager(this);
    shop_ = new Shop(player_, this);

    dialogueBox_ = new DialogueBox(this);
    dialogueBox_->changeText("DialogueBox1");
    dialogueBox_->show();

    info = new UI_Info(this);
    auto* x = new Bed(this);
    x->setPosition(500, 300);
    add(x);
}

void Game::update()
{
    player_->update();

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
    int bgWidth = mapInfo.tile_width * mapInfo.cols;
    int bgHeight = mapInfo.tile_height * mapInfo.rows;
    SDL_Rect r = { 0,0, bgWidth, bgHeight };

    //mapInfo.tilesets[tset_gid]->render(src, dest);
    SDL_RenderCopy(renderer, background, NULL, &r);

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
        if(gameObjects_[i]->collide(rect)){
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
    addEnemies(new Cat(this, 50, Point2D<int>(100, 100),animationManager));
    addEnemies(new Bat(this, 20, Point2D<int>(200, 300), 7,animationManager));
    addEnemies(new Bull(this, 35, Point2D<int>(350, 70),animationManager));
    addEnemies(new Scorpion(this, 80, Point2D<int>(100, 100), animationManager));
    addEnemies(new Plant(this, 60, Point2D<int>(200, 100), animationManager));
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
    //SDL_Texture* background = SDL_CreateTexture(rend,
    background = SDL_CreateTexture(rend,

        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        bgWidth,
        bgHeight
    );
    SDL_RenderClear(renderer);
    SDL_SetTextureBlendMode(background, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, background);
    

    //Establecemos los bordes de la camara con respecto al tamaño del tilemap
        //Camera::mainCamera->setBounds(0, 0, mapInfo.cols * mapInfo.tile_width, mapInfo.rows * mapInfo.tile_height);

    //Cargamos y almacenamos los tilesets utilizados por el tilemap
    // (el mapa utiliza el �ndice [gid] del primer tile cargado del tileset como clave)
    // (para poder cargar los tilesets del archivo .tmx, les ponemos de nombre 
    // el nombre del archivo sin extension en el .json) 
    auto& mapTilesets = mapInfo.tile_map->getTilesets();
    for (auto& tileset : mapTilesets) {
        string name = tileset.getName();
        Texture* texture = tilesets_.find(name)->second;//&sdlutils().tilesets().find(name)->second;
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
                   
                    if (tileRot %2 == 1) 
                        tileRot = 90;
                    
                    //Multiplicamos por 45 porque esta multiplicado por factor de 45 (lo que devuelve rot)
                    mapInfo.tilesets[tset_gid]->render(src, dest, tileRot * 45, nullptr, );
                }
            }
        }
    }

    SDL_SetRenderTarget(renderer, nullptr);
}