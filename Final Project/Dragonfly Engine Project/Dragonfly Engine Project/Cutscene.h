#pragma once

#include "Object.h"

class Cutscene : public df::Object {
private:
	int count;
	int type;
	void deleteOthers();
	int npcs;
	int clues;

public:
	Cutscene(int t = 0, df::Color c = df::WHITE);

	int getEndType();
	void getScore();
	int eventHandler(const df::Event* p_e) override;
	void setColor(df::Color c);
	int draw() override;
};