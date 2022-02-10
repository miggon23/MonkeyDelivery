#pragma once
class State;

class StateMachine
{
protected:
	State* state = nullptr;
	State* savedState = nullptr;

public:
	void setState(State* state);
	void saveState(State* state);

	State* getState();
	State* getSavedState();

	void clearSavedState();
};

