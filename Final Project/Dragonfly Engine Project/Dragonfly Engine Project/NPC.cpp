#include "NPC.h"
#include "DisplayManager.h"
#include <cstdlib>
#include "WorldManager.h"
#include "Room.h"
#include "EventStep.h"
#include "LogManager.h"
#include "EventRoomLoaded.h"

NPC::NPC() : NPC(df::WHITE) {}

NPC::NPC(df::Color npc_color)
{
	isMurd = false;
	isHunting = false;

	roomPos = df::Vector(0, 1);
	mapPos = df::Vector(DM.getHorizontal() / 2, DM.getVertical() / 2);
	setPosition(mapPos);
	patience = -1;
	stateCooldown = 0;
	roamCooldown = 0;
	state = "idle";
	roamX = 0;
	roamY = 0;
	target = 0;

	// set sprite
	setColor(npc_color);
	// set type
	setType("NPC");

	setSolidness(df::SOFT);
	setAltitude(1);

	if (inLoadedRoom()) {
		loadNPC();
	}
	else {
		unloadNPC();
	}
}

void NPC::setColor(df::Color npc_color) {
	color = npc_color;
	std::string spriteTag;
	switch (color) {
	case df::RED:
		spriteTag = "_R";
		break;
	case df::GREEN:
		spriteTag = "_G";
		break;
	case df::BLUE:
		spriteTag = "_B";
		break;
	case df::CYAN:
		spriteTag = "_C";
		break;
	case df::YELLOW:
		spriteTag = "_Y";
		break;
	case df::MAGENTA:
		spriteTag = "_M";
		break;
	case df::WHITE:
	default:
		spriteTag = "";
	}

	if (isHunting)
	{
		setSprite("Murd" + spriteTag);
	}
	else {
		setSprite("NPC" + spriteTag);
	}
}

std::string NPC::getColorString() const
{
	switch (color) {
	case df::RED:
		return "Red";
	case df::GREEN:
		return "Green";
	case df::BLUE:
		return "Blue";
	case df::CYAN:
		return "Cyan";
	case df::YELLOW:
		return "Yellow";
	case df::MAGENTA:
		return "Magenta";
	case df::WHITE:
	default:
		return "White";
	}
}

void NPC::setRoomPos(df::Vector new_room) {
	roomPos = new_room;
}

df::Vector NPC::getRoomPos() const {
	return roomPos;
}

void NPC::setMurd(bool murd)
{
	isMurd = murd;
	setHunt(murd);

	LM.writeLog("Chosen Murderer: %s %d\n", getColorString().c_str(), isMurd);
}

bool NPC::getMurd() const
{
	return isMurd;
}

void NPC::setHunt(bool hunt)
{
	isHunting = hunt;
	setColor(color);
}

bool NPC::getHunt() const
{
	return isHunting;
}

void NPC::loadNPC() {
	loaded = true;
	setPosition(mapPos);
}

void NPC::unloadNPC() {
	if (loaded)
	{
		mapPos = getPosition();
		LM.writeLog("Stored pos: (%f, %f)\n", mapPos.getX(), mapPos.getY());
	}
	loaded = false;
	setPosition(df::Vector(-100, -100));
}

void NPC::roam() {
	target = -1;
	if (patience <= -1) {
		patience = (std::rand() % 210) + 90;
	}

	if (patience != 0) {
		if (state == "idle" && stateCooldown > 0) {
			stateCooldown--;
		}
		else if (state == "roaming" && stateCooldown > 0) {
			if (roamCooldown == 0) {
				df::Vector new_pos = df::Vector(mapPos.getX() + roamX, mapPos.getY() + roamY);
				if (new_pos.getY() > 5 && new_pos.getY() < DM.getVertical() - 5 && new_pos.getX() > 20 && new_pos.getX() < DM.getHorizontal() - 20) {
					mapPos.setXY(new_pos.getX(), new_pos.getY());
					WM.moveObject(this, mapPos);
				}
				roamCooldown = 15;
			}
			roamCooldown--;
			stateCooldown--;
		}
		else {
			int choose = std::rand() % 2;
			if (choose == 0) {
				LM.writeLog("Going into idle\n");
				state = "idle";
				stateCooldown = (std::rand() % 300) + 30;
			}
			else if (choose == 1) {
				LM.writeLog("Going into roam\n");
				state = "roaming";
				stateCooldown = (std::rand() % 300) + 30;
				roamX = (std::rand() % 3) - 1;
				roamY = (std::rand() % 3) - 1;
			}
		}
	}
	else {
		state = "leaving";
	}
}

bool NPC::inLoadedRoom() {
	Room* room = dynamic_cast<Room*>(WM.objectsOfType("room")[0]);
	return room->getCurrentPos() == roomPos;
}

int NPC::eventHandler(const df::Event* p_e) {
	// if a step event occurs, call step
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	//if (p_e->getType() == ROOM_LOADED_EVENT) {
	//	LM.writeLog("Room Loaded. NPC position: (%f, %f)\n", getRoomPos().getX(), getRoomPos().getY());
	//	return 1;
	//}
	return 0;
}

// Function that holds most of the AI logic. Does not include the logic for the murder yet
void NPC::step() {
	if (inLoadedRoom()) { // if the NPC is in the room with the player
		loadNPC(); // Load NPC at their room position
		if (state != "leaving") { // if they are not set to leave,
			//setColor(df::GREEN);
			roam(); // have them roam around the room making either random movements or just idling
		}
		else {
			//setColor(df::RED);
			leave(); // if state is set to leave, have them find the nearest exit and go out that way
		}
	}
	else {
		unloadNPC(); // Move the NPC to a position off screen while still presevering where their room position is
		stall(); // wait around for a certain amount of time before deciding to go to a random adjacent room
	}
	patience--;
}

void NPC::stall() {
	target = -1;
	if (patience <= -1) {
		patience = (std::rand() % 210) + 90; // will wait between 3 - 10 seconds within a room
	}

	if (patience == 0) {
		int roll = std::rand() % 4;
		int x_move = (1 - (roll % 2)) * (roll - 1); // if roll = 0, move west; if roll = 2, move east
		int y_move = (roll % 2) * (roll - 2); // if roll = 1, move north; if roll = 3, move south
		df::Vector new_vec = df::Vector(roomPos.getX() + x_move, roomPos.getY() + y_move);
		while (new_vec.getX() < 0 || new_vec.getX() > 3 || new_vec.getY() < 0 || new_vec.getY() > 3) {
			roll = std::rand() % 4;
			x_move = x_move = (1 - (roll % 2)) * (roll - 1);
			y_move = y_move = (roll % 2) * (roll - 2);
			new_vec.setXY(roomPos.getX() + x_move, roomPos.getY() + y_move);
		}
		setRoomPos(new_vec);

		loadNPC();
		if (inLoadedRoom())
		{
			switch (roll) {
			case 0:	// West
				setPosition(df::Vector(DM.getHorizontal() - 21, DM.getVertical() / 2));
				break;
			case 1:	// North
				setPosition(df::Vector(DM.getHorizontal() / 2, DM.getVertical() - 5));
				break;
			case 2:	// East
				setPosition(df::Vector(21, DM.getVertical() / 2));
				break;
			case 3:	// South
				setPosition(df::Vector(DM.getHorizontal() / 2, 5));
				break;
			}
		}
		else {
			setPosition(df::Vector(std::rand() % (DM.getHorizontal() - 42) + 21, std::rand() % (DM.getVertical() - 10) + 5));
		}
		unloadNPC();

		//LM.writeLog("Changing rooms to new room %f, %f\n", new_vec.getX(), new_vec.getY());
	}
}

void NPC::leave() { // walk to a random exit of the room
	patience = -1;
	if (target == -1)
	{
		// Select room to move to
		Room* room = (Room*)WM.objectsOfType("room")[0];
		bool* doors = room->getDoors();
		while ((target < 0 || !doors[target])) {
			target = std::rand() % 4;
			//LM.writeLog("Door chosen: %d, Valid: %d\n", target, doors[target]);
		}
		free(doors);

		//LM.writeLog("TargetDoor: %d\n", target);
	}
	int targetX, targetY;
	switch (target) {
	case 0:	// Move to North
		targetX = DM.getHorizontal() / 2;
		targetY = 5;
		break;
	case 1:	// Move to East
		targetX = DM.getHorizontal() - 21;
		targetY = DM.getVertical() / 2;
		break;
	case 2:	// Move to South
		targetX = DM.getHorizontal() / 2;
		targetY = DM.getVertical() - 5;
		break;
	case 3:	// Move to West
		targetX = 21;
		targetY = DM.getVertical() / 2;
		break;
	}

	if (targetX > getPosition().getX()) { // Find X roam
		roamX = 1;
	}
	else if (targetX < getPosition().getX()) {
		roamX = -1;
	}
	else {
		roamX = 0;
	}

	if (targetY > getPosition().getY()) { // Find Y roam
		roamY = 1;
	}
	else if (targetY < getPosition().getY()) {
		roamY = -1;
	}
	else {
		roamY = 0;
	}

	if (roamX == 0 && roamY == 0 && roamCooldown == 0)
	{
		df::Vector newRoomPos;
		switch (target) {
		case 0:	// Move to North
			setPosition(df::Vector(getPosition().getX(), getPosition().getY() + 13));
			newRoomPos = df::Vector(getRoomPos().getX(), getRoomPos().getY() - 1);
			roamX = (std::rand() % 3) - 1;
			roamY = (std::rand() % 2) - 1;
			break;
		case 1:	// Move to East
			setPosition(df::Vector(getPosition().getX() - 38, getPosition().getY()));
			newRoomPos = df::Vector(getRoomPos().getX() + 1, getRoomPos().getY());
			roamX = (std::rand() % 2);
			roamY = (std::rand() % 3) - 1;
			break;
		case 2:	// Move to South
			setPosition(df::Vector(getPosition().getX(), getPosition().getY() - 13));
			newRoomPos = df::Vector(getRoomPos().getX(), getRoomPos().getY() + 1);
			roamX = (std::rand() % 3) - 1;
			roamY = (std::rand() % 2);
			break;
		case 3:	// Move to West
			setPosition(df::Vector(getPosition().getX() + 38, getPosition().getY()));
			newRoomPos = df::Vector(getRoomPos().getX() - 1, getRoomPos().getY());
			roamX = (std::rand() % 2) - 1;
			roamY = (std::rand() % 3) - 1;
			break;
		}
		//LM.writeLog("NPC on screen move to: (%f, %f) (from (%f, %f), target %d)", newRoomPos.getX(), newRoomPos.getY(),
		//	getRoomPos().getX(), getRoomPos().getY(), target);
		setRoomPos(newRoomPos);
		roamCooldown = 15;
		unloadNPC();
		state = "roaming";
		stateCooldown = (std::rand() % 100) + 30;
		return;
	}

	//LM.writeLog("Target Door: %d, Target Pos: (%d, %d), Roam: (%d, %d)\n", target, targetX, targetY, roamX, roamY);

	if (roamCooldown == 0) {	// Roam towards door
		df::Vector new_pos = df::Vector(mapPos.getX() + roamX, mapPos.getY() + roamY);
		if (new_pos.getY() > 4 && new_pos.getY() < DM.getVertical() - 4 && new_pos.getX() > 20 && new_pos.getX() < DM.getHorizontal() - 20) {
			mapPos.setXY(new_pos.getX(), new_pos.getY());
			WM.moveObject(this, mapPos);
		}
		else {
			LM.writeLog("!!err: OOB!!\n");
		}
		roamCooldown = 15;
	}
	roamCooldown--;
}