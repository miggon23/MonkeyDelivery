#include "StateMachine.h"
#include "State.h"

void StateMachine::setState(State* state) {
	if(getState() != nullptr)
		getState()->onExitState();
	this->state = state;
	state->onEnterState();
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