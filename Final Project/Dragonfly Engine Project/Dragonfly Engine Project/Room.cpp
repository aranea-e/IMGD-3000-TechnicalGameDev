#include "Room.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "LogManager.h"
#include "EventRoom.h"
#include "EventRoomLoaded.h"
#include "ResourceManager.h"

void Room::init(std::string r_sprite_name, std::string bottom_wall, df::Vector r_pos)
{
	setSprite(r_sprite_name);
	setType("room");
	setSolidness(df::SPECTRAL);
	setAltitude(0);
	setPosition(df::Vector(DM.getHorizontal() / 2, DM.getVertical() / 2));
	roomPos = r_pos;
	bottomWall = df::Animation();
	bottomWall.setSprite(RM.getSprite(bottom_wall));
	LM.writeLog("Room Loaded: %s (%.0f, %.0f)\n", r_sprite_name.c_str(), roomPos.getX(), roomPos.getY());
}

Room::Room() : Room(df::Vector(0, 0)) {}

Room::Room(df::Vector r_pos)
{
	init(RoomToString(r_pos), RoomBottomWall(PosToRoom(r_pos)), r_pos);
}

df::Vector Room::getCurrentPos() {
	return roomPos;
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
	init(RoomToString(new_pos), RoomBottomWall(PosToRoom(new_pos)), new_pos);
	EventRoomLoaded* p_rl = new EventRoomLoaded(new_pos, old_pos);
	WM.onEvent(p_rl);
}

bool* Room::getDoors()
{
	bool* out = new bool[4];
	out[0] = (roomPos.getY() != 0); // North
	out[1] = (roomPos.getX() != 3); // East
	out[2] = (roomPos.getY() != 3); // South
	out[3] = (roomPos.getX() != 0); // West
	//LM.writeLog("%d, %d, %d, %d\n", out[0], out[1], out[2], out[3]);
	return out;
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

std::string Room::RoomToString(df::Vector pos)
{
	int x, y;
	x = (int)pos.getX();
	y = (int)pos.getY();
	return "Room_" + std::to_string(x) + std::to_string(y);
}

std::string Room::RoomToString()
{
	return RoomToString(roomPos);
}

std::string Room::RoomBottomWall(RoomType r_type)
{
	switch (r_type) {
	case BL:
	case BM:
	case BR:
		return "Room_W_N";
	case ML:
	case MR:
	case TL:
	case TM:
	case MM:
	default:
		return "Room_W_D";
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

int Room::draw() {
	if (getAltitude() == 3)
	{
		//LM.writeLog("Drew");
		setAltitude(0);
		return bottomWall.draw(df::Vector(getPosition().getX(), getPosition().getY() + 9.5));
	} 
	setAltitude(3);
	return Object::draw();
}