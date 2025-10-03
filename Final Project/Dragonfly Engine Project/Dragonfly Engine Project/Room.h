#pragma once
// System Includes
#include <string>

// Engine Includes
#include "Object.h"

// Game Includes

class Room : public df::Object {
private:
public:
	Room();
	Room(std::string r_sprite_name);
};