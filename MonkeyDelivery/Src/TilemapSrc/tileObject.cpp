#include "tileObject.h"

void tileObject::setDest(int x, int y, int w, int h) {
  dest.x=x;
  dest.y=y;
  dest.w=w;
  dest.h=h;
}
void tileObject::setSource(int x, int y, int w, int h) {
  src.x=x;
  src.y=y;
  src.w=w;
  src.h=h;
}
void tileObject::setImage(string filename, SDL_Renderer* ren) {

  SDL_Surface* surf = IMG_Load(filename.c_str());
  tex = SDL_CreateTextureFromSurface(ren, surf);

}
