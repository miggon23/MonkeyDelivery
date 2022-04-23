#pragma once
#include "GameObject.h"

class MissionsPanel;

class Target : public GameObject
{
public:
	Target(MissionsPanel* mp, Game* g);
	Target(MissionsPanel* mp, Game* g, string texture);
	~Target();

	void onPlayerInteraction(Player* player) override;
	void update() override;
	void draw() override;

	inline void changeActive() {
		active_ = !active_;
	};

	inline bool isActive() {
		return active_;
	}

	void setTexture(string tex);

	inline void setText(const string& textName) {
		textPath_ = textName + "Text";
	};

private:
	MissionsPanel* missionsPanel_;
	bool active_;
	string textPath_;
};