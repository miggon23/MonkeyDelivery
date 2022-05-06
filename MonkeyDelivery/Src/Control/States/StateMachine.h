#pragma once
#include <vector>
class State; 
class Button;


class StateMachine
{
protected:
	State* state = nullptr;
	State* optionsState=nullptr;
	std::vector<State*> savedStates;	
public:
	~StateMachine() {};

	void setState(State* state);
	void setSaveState(State* state);
	inline void setOptionsState(State* state) { optionsState = state; };

	inline State* getState() { return this->state; };
	State* getSavedState();
	inline State* getOptionsState() { return optionsState; };

	void removeSavedState();
	inline bool saveStateEmpty() { return savedStates.empty(); };
	void clearSavedState();
	inline void ClearState() { state = nullptr; };
};