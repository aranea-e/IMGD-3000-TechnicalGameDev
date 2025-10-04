#include "Room.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "EventRoom.h"
#include "EventRoomLoaded.h"

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

Room::Room() : Room(df::Vector(0, 0)) {}

Room::Room(df::Vector r_pos)
{
	init(RoomToString(PosToRoom(r_pos)), r_pos);
}

int Room::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == ROOM_EVENT) {
		const EventRoom* p_room_event =
			dynamic_cast <const EventRoom*> (p_e);
		moveRoom(p_room_event->getPos());
		return 1;
	}

	return 0;
}

void Room::moveRoom(df::Vector r_move)
{

	if (!(r_move.getX() == 0 || r_move.getX() == -1 || r_move.getX() == 1) ||
		!(r_move.getY() == 0 || r_move.getY() == -1 || r_move.getY() == 1)) {
		LM.writeLog("!!moveRoom given value other than 0, 1, -1!!\n");
		return;
	}
	df::Vector new_pos = roomPos;
	new_pos = new_pos + r_move;
	if (new_pos.getX() < 0 || new_pos.getX() > 3 || new_pos.getY() < 0 || new_pos.getY() > 3) {
		LM.writeLog("!!moveRoom out of bounds!!\nBad Pos: (%f, %f)\n%d%d%d%d\n", new_pos.getX(), new_pos.getY(),
			r_move.getX() < 0, r_move.getX() > 3, r_move.getY() < 0, r_move.getY() > 3);
		return;
	}
	df::Vector old_pos = roomPos;
	init(RoomToString(PosToRoom(new_pos)), new_pos);
	EventRoomLoaded* p_rl = new EventRoomLoaded(new_pos, old_pos);
	WM.onEvent(p_rl);
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
