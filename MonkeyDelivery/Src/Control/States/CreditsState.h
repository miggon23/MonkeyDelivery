#pragma once
#include "State.h"

class CreditsState : public State
{
public:
	CreditsState(Game* game);
	~CreditsState() = default;
	
	void draw()override;
	void update()override;

	void loadCredits(std::string filename);

	inline void next()override {};
	inline void onExitState() override {};
	void onEnterState() override;

	string getStateName() const {
		return "Credits state";
	};

	void registerCommands()override;

	inline Button* getCurrentButton() override { return buttonsUI[0]; };

private:
	Texture* backgroundTexture;
	Texture* selectorTexture;

	const int buttonW = 300, buttonH = 140;
	vector<std::string> credits_; 
	const int xOffset_ = 400, yOffset_ = 100, ySize_ = 50;
	const int timeNewName_ = 1000;

	int lastName_, index_ = 0;
};