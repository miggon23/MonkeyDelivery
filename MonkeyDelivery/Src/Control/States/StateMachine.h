#pragma once
#include <vector>
class State; 
class Button;
class StateMachine
{
protected:
	State* state = nullptr;
	//State* savedState = nullptr;
	std::vector<State*> savedStates;
public:
	void setState(State* state);
	void setSaveState(State* state);

	State* getState();
	State* getSavedState();
	void removeSavedState();
	inline bool saveStateEmpty() { return savedStates.empty(); };
	void clearSavedState();
	void ClearState() { state = nullptr; };
};

