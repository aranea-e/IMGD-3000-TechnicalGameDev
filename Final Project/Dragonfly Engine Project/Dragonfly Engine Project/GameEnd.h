#pragma once

#include "Object.h"

class GameEnd : public df::Object {
private:
	int m_type;
	void end();
	void restart(); // restarts the game skipping the game start screen
public:
	GameEnd(int type = 0);	// End game with type (0 = win, 1 = death, 2 = wrong target, 3 = quit)
	int eventHandler(const df::Event* p_e) override;
};