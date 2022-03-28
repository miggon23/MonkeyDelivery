#include "StateMachine.h"
#include "State.h"
void StateMachine::setState(State* state) {	
	this->state = state;
}

State* StateMachine::getState() {
	return this->state;
}

void StateMachine::setSaveState(State* state) {
	savedStates.push_back(state);
}

State* StateMachine::getSavedState(){
	auto x= savedStates.end();
	x--;
	return *x;
}

void StateMachine::removeSavedState(){
	auto x = savedStates.end();
	x--;
	savedStates.erase(x);
}

void StateMachine::clearSavedState(){
	for (auto it : savedStates) {
		delete it;
	}
	savedStates.clear();
}
