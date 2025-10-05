#pragma once

#include "Object.h"

class GameEnd : public df::Object {
private:
	int m_type;
	void end();
public:
	GameEnd(int type = 0);	// End game with type (0 = win, 1 = death, 2 = wrong target, 3 = quit)
};