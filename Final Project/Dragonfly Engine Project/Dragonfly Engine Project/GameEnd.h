#pragma once

#include "Object.h"

class GameEnd : public df::Object {
private:
	int m_type;
	int m_npcs;
	int m_clues;
	int m_score;
	void end();
	void restart(); // restarts the game skipping the game start screen
public:
	GameEnd(int type = 0, int npcs = 0, int clues = 0);	// End game with type (0 = win, 1 = death, 2 = wrong target, 3 = quit)
	int eventHandler(const df::Event* p_e) override;
	int draw() override;
};