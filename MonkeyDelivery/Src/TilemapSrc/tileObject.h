#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
using namespace std;
#include <SDL.h>
#include <SDL_image.h>

class tileObject {
private:
SDL_Rect dest;
SDL_Rect src;
SDL_Texture* tex;
bool solid;
public:
	tileObject() {solid=1;}
SDL_Rect getDest() const {return dest;}
SDL_Rect getSource() const {return src;}
void setDest(int x, int y, int w, int h);
void setSource(int x, int y, int w, int h);
void setImage(string filename, SDL_Renderer* ren);
SDL_Texture* getTex() const {return tex;}
void setSolid(bool s) {solid=s;}
bool getSolid()const {return solid;}
};


#endif //OBJECT_H
