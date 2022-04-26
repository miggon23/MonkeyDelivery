#pragma once
#include "GameObject.h"

class MissionsPanel;

class MissionObject : public GameObject
{
public:
	MissionObject(MissionsPanel* mp, Game* g);
	~MissionObject();

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

