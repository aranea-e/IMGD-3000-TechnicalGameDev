#include "Room.h"
#include "DisplayManager.h"

Room::Room() : Room("Room_MM") {}

Room::Room(std::string r_sprite_name)
{
	setSprite(r_sprite_name);
	setType("room");
	setSolidness(df::SPECTRAL);
	setAltitude(0);

	setPosition(df::Vector(DM.getHorizontal() / 2, DM.getVertical() / 2));
}
