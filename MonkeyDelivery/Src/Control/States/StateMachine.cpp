#include "StateMachine.h"
#include "State.h"

void StateMachine::setState(State* state) {
	this->state = state;
}

State* StateMachine::getState() {
	return this->state;
}

void StateMachine::saveState(State* state) {
	savedState = state;
}

State* StateMachine::getSavedState() {
	return savedState;
}

void StateMachine::clearSavedState() {
	savedState = nullptr;
}
