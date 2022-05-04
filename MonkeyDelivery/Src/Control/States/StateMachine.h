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
	~StateMachine();

	void setState(State* state);
	void setSaveState(State* state);
	void setOptionsState(State* state);

	State* getState();
	State* getSavedState();
	State* getOptionsState();

	void removeSavedState();
	inline bool saveStateEmpty() { return savedStates.empty(); };
	void clearSavedState();
	void ClearState() { state = nullptr; };
};