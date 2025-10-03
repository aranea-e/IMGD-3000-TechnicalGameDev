#include "Room.h"
#include "DisplayManager.h"
#include "LogManager.h"

void Room::init(std::string r_sprite_name, df::Vector r_pos)
{
	setSprite(r_sprite_name);
	setType("room");
	setSolidness(df::SPECTRAL);
	setAltitude(0);
	setPosition(df::Vector(DM.getHorizontal() / 2, DM.getVertical() / 2));
	roomPos = r_pos;
	LM.writeLog("Room Loaded: %s\n", r_sprite_name.c_str());
}

Room::Room() 
{
	init("Room_MM");
}

Room::Room(df::Vector r_pos)
{
	init(RoomToString(PosToRoom(r_pos)), r_pos);
}

std::string Room::RoomToString(RoomType r_type)
{
	switch (r_type) {
	case BL:
		return "Room_BL";
	case BM:
		return "Room_BM";
	case BR:
		return "Room_BR";
	case ML:
		return "Room_ML";
	case MR:
		return "Room_MR";
	case TL:
		return "Room_TL";
	case TM:
		return "Room_TM";
	case TR:
		return "Room_TR";
	case MM:
	default:
		return "Room_MM";
	}
}

RoomType Room::PosToRoom(df::Vector r_pos)
{
	int x, y;
	x = (int)r_pos.getX();
	y = (int)r_pos.getY();

	if (x == 0)
	{
		if (y == 0)
		{
			return TL;
		}
		else if (y == 3) {
			return BL;
		}
		else {
			return ML;
		}
	}
	else if (x == 3) {
		if (y == 0)
		{
			return TR;
		}
		else if (y == 3) {
			return BR;
		}
		else {
			return MR;
		}
	}
	else {
		if (y == 0)
		{
			return TM;
		}
		else if (y == 3) {
			return BM;
		}
		else {
			return MM;
		}
	}
}
