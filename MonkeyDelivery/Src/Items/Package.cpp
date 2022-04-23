#include "Package.h"

Package::Package(Texture* tex, Game* game,Player* player) : InventoryObject(tex, game,player)
{
	setTypeObject(PACKAGE);
}
