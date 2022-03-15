#include "Flashlight.h"
#include "Player.h"

Flashlight::Flashlight() : active(false)
{
}

bool Flashlight::useObject() {
	if (!active) {
		cout << " Hola linternita";
	}
	else {
		cout << "Adios linternita";
	}
	cout << endl;
	active = !active;
	return false; //devolvemos false indicando que el objeto no debe destruirse tras ser usado
}


