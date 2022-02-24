#include "InventoryObject.h"

InventoryObject::InventoryObject(Game* game) : game_(game)
{
}

InventoryObject::~InventoryObject()
{
}

/// <summary>
/// Método virtual que realiza el uso del objeto y devuelve si el objeto es deshechable(true) o reutilizable
/// </summary>
/// <returns>True si el objeto debe ser eliminado del inventario o false si se debe mantener</returns>
bool InventoryObject::useObject()
{
	return false;
}
