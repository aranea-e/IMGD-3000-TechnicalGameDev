#pragma once

// Engine includes
#include "Object.h"

class GameStart : public df::Object {
private:
	void start();

public:
	GameStart();
	int eventHandler(const df::Event* p_e) override;
};