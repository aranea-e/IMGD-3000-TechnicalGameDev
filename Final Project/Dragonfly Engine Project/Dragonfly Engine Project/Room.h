#pragma once
// System Includes
#include <string>

// Engine Includes
#include "Object.h"
#include "Animation.h"

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

	void init(std::string r_sprite_name, std::string bottom_wall, df::Vector r_pos = df::Vector(0,0));	// Initializes values

	std::string RoomToString(RoomType r_type);	// Converts RoomType to string
	std::string RoomBottomWall(RoomType r_type);// Gets the bottom wall string for room
	RoomType PosToRoom(df::Vector r_pos);		// Gets RoomType for pos

	df::Animation bottomWall;	// Animation to prevent overlapping with bottom wall

public:
	Room();					// Default constructor (0, 0)
	Room(df::Vector r_pos);	// Position constructor

	df::Vector getCurrentPos(); // get the current room player is in

	int eventHandler(const df::Event* p_e) override;	// Event Handler

	void moveRoom(df::Vector r_move);	// Changes rooms. Requires vector with values 0, 1, or -1.
	bool* getDoors();					// Gets all doors to current room. Returned as an array with [N,E,S,W]

	int draw();	// Draw bottom wall separate (to prevent chars from overlapping it)
};