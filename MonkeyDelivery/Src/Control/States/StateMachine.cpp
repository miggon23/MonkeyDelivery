#include "StateMachine.h"
#include "State.h"

void StateMachine::setState(State* state) {
	if(this->savedState!=this->state)delete this->state;
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
	if(savedState!=nullptr)savedState = nullptr;
}
