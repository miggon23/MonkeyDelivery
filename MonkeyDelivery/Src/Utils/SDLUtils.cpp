// This file is part of the course TPV2@UCM - Samir Genaim

#include "SDLUtils.h"
#include "SoundManager.h"

#include <cassert>


SDLUtils::SDLUtils() :
		SDLUtils("SDL Demo", 600, 400) {
}

SDLUtils::SDLUtils(std::string windowTitle, int width, int height) :
		windowTitle_(windowTitle), width_(width), height_(height) {
	initWindow();
	initSDLExtensions();
}

SDLUtils::SDLUtils(std::string windowTitle, int width, int height,
		std::string filename) : SDLUtils(windowTitle, width, height) {
	loadReasources(filename);

	SDL_Surface* icon = IMG_Load("./resources/icons/gameIcon.png");
	SDL_SetWindowIcon(window_, icon);
}

SDLUtils::~SDLUtils() {
	closeSDLExtensions();
	closeWindow();
}

void SDLUtils::initWindow() {
	// initialise SDL
	int sdlInit_ret = SDL_Init(SDL_INIT_EVERYTHING);
	assert(sdlInit_ret == 0);

	// Create window
	window_ = SDL_CreateWindow(windowTitle_.c_str(),
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_SHOWN);
	assert(window_ != nullptr);

	// Create the renderer
	renderer_ = SDL_CreateRenderer(window_, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(renderer_ != nullptr);
}

void SDLUtils::closeWindow() {

	// destroy renderer and window
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);

	SDL_Quit(); // quit SDL
}

void SDLUtils::initSDLExtensions() {

	// initialize SDL_ttf
	int ttfInit_r = TTF_Init();
	assert(ttfInit_r == 0);

	// initialize SDL_image
	int imgInit_ret = IMG_Init(
			IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
	assert(imgInit_ret != 0);

	// initialize SDL_mixer
	soundManager().initMixer();
}

void SDLUtils::loadReasources(std::string filename) {
	// TODO check the correctness of values and issue a corresponding
	// exception. Now we just do some simple checks, and assume input
	// is correct.

	// load JSON configuration file
	JSONValue* jAux = JSON::ParseFromFile(filename);

	// check it was loaded correctly
	// the root must be a JSON object
	if (jAux == nullptr || !jAux->IsObject()) {
		throw "Something went wrong while load/parsing '" + filename + "'";
	}

	// we know the root is JSONObject
	JSONObject root = jAux->AsObject();

	// TODO improve syntax error checks below, now we do not check
	//      validity of keys with values as sting or integer

	// load fonts
	JSONValue* jValue = root["fonts"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
					uint8_t size =
							static_cast<uint8_t>(vObj["size"]->AsNumber());
					fonts_.emplace(key, Font(file, size));
				} else {
					throw "'fonts' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'fonts' is not an array in '" + filename + "'";
		}
	}

	// load images
	jValue = root["images"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
					images_.emplace(key, Texture(renderer(), file));
				} else {
					throw "'images' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'images' is not an array in '" + filename + "'";
		}
	}

	// load sounds
	jValue = root["sounds"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					int volume = vObj["volume"]->AsNumber();
					std::string file = vObj["file"]->AsString();
					soundManager().addSFX(key, file, volume);
				} else {
					throw "'sounds' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'sounds' is not an array";
		}
	}

	// load musics
	jValue = root["musics"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			for (auto &v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
					soundManager().addMusic(key, file);
				} else {
					throw "'musics' array in '" + filename
							+ "' includes and invalid value";
				}
			}
		} else {
			throw "'musics' is not an array";
		}
	}

	// cargamos los volumenes en cada sonido/musica
	soundManager().setMusicVolume(soundManager().getMusicVolume());
	soundManager().setSFXVolume(soundManager().getSFXVolume());

	// load tilesets
	jValue = root["tilesets"];
	if (jValue != nullptr) {
		if (jValue->IsArray()) {
			for (auto& v : jValue->AsArray()) {
				if (v->IsObject()) {
					JSONObject vObj = v->AsObject();
					std::string key = vObj["id"]->AsString();
					std::string file = vObj["file"]->AsString();
					tilesets_.emplace(key, Texture(renderer(), file));
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

	delete jAux;
}

void SDLUtils::closeSDLExtensions() {
	images_.clear();
	fonts_.clear();
	tilesets_.clear();

	TTF_Quit(); // quit SDL_ttf
	IMG_Quit(); // quit SDL_image
}