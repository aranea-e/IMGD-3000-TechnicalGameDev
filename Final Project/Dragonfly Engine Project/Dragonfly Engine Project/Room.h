#pragma once
// System Includes
#include <string>

// Engine Includes
#include "Object.h"

// Game Includes

enum RoomType {
	BL,
	BM,
	BR,
	ML,
	MM,
	MR,
	TL,
	TM,
	TR,
};

class Room : public df::Object {
private:
	df::Vector roomPos;	// Position in world, (0, 0) to (3, 3)

	void init(std::string r_sprite_name, df::Vector r_pos = df::Vector(0,0));	// Initializes values

	std::string RoomToString(RoomType r_type);	// Converts RoomType to string
	RoomType PosToRoom(df::Vector r_pos);		// Gets RoomType for pos

public:
	Room();					// Default constructor (0, 0)
	Room(df::Vector r_pos);	// Position constructor

	int eventHandler(const df::Event* p_e) override;	// Event Handler

	void moveRoom(df::Vector r_move);	// Changes rooms. Requires vector with values 0, 1, or -1.
};