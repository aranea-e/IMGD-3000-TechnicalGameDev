#pragma once

#include "Object.h"

class Cutscene : public df::Object {
private:
	int count;
	int type;
	void deleteOthers();
public:
	Cutscene(int t = 0, df::Color c = df::WHITE);
	int eventHandler(const df::Event* p_e) override;
	void setColor(df::Color c);
};