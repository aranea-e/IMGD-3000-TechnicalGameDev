#include "NPC.h"
#include "DisplayManager.h"
#include <cstdlib>
#include <algorithm>
#include "WorldManager.h"
#include "Room.h"
#include "EventStep.h"
#include "LogManager.h"
#include "EventRoomLoaded.h"
#include "Cutscene.h"
#include "ObjectList.h"
#include "ResourceManager.h"
#include "GameManager.h"

NPC::NPC(df::Color npc_color, df::Vector pos)
{
	isMurd = false;
	isHunting = false;
	alive = true;

	roomPos = pos;
	setMapPos(df::Vector((float)(std::rand() % (DM.getHorizontal() - 42) + 21), (float)(std::rand() % (DM.getVertical() - 10) + 5)));
	setPosition(mapPos);
	patience = -1;
	stateCooldown = 0;
	roamCooldown = 0;
	state = "idle";
	roamX = 0;
	roamY = 0;
	target = 0;
	seen = 60;
	murdReaction = 45;
	murdWait = -1;
	murdTimer = -1;

	// set sprite
	setSprite("NPC_L");
	color = npc_color;
	updateSprite();
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
}

void NPC::updateSprite() {
	std::string tag = "_L";
	if (faceRight)
	{
		tag = "_R";
	}

	if (!alive)
	{
		if (getAnimation().getSprite()->getLabel() != "Dead")
		setSprite("Dead");
	}
	else if (isHunting)
	{
		if (getAnimation().getSprite()->getLabel() != "Murd" + tag)
		setSprite("Murd" + tag);
	}
	else {
		if (beingChased())
		{
			if (getAnimation().getSprite()->getLabel() != ("NPCp" + tag))
			setSprite("NPCp" + tag);

		}
		else if (moving) {
			if (getAnimation().getSprite()->getLabel() != ("NPCw" + tag))
			setSprite("NPCw" + tag);
		}
		else {
			if (getAnimation().getSprite()->getLabel() != ("NPC" + tag))
			setSprite("NPC" + tag);
		}
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

df::Color NPC::getColor() const
{
	return color;
}

void NPC::setRoomPos(df::Vector new_room) {
	roomPos = new_room;
}

df::Vector NPC::getRoomPos() const {
	return roomPos;
}

void NPC::setMapPos(df::Vector new_mpos)
{
	if (new_mpos.getY() <= 4 || new_mpos.getY() >= DM.getVertical() - 4 || new_mpos.getX() <= 20 || new_mpos.getX() >= DM.getHorizontal() - 20)
	{
		LM.writeLog("!!Err: OOB (In: SetMapPos)!!\n");
		return;
	}
	mapPos = new_mpos;
}

void NPC::die()
{
	if (inLoadedRoom() && alive)
	{
		RM.getSound("NPC_Death")->play();
	}
	if (alive)
	{
		LM.writeLog("NPC Killed: %s\n", getColorString().c_str());
	}
	alive = false;
	setAltitude(1);
	updateSprite();
}

void NPC::setMurd(bool murd)
{
	isMurd = murd;
	LM.writeLog("Chosen Murderer: %s %d\n", getColorString().c_str(), isMurd);
}

bool NPC::getMurd() const
{
	return isMurd;
}

void NPC::setHunt(bool hunt, bool huntplayer)
{
	isHunting = hunt;
	isHuntPlayer = huntplayer;
	updateSprite();
}

bool NPC::getHunt() const
{
	return isHunting;
}

bool NPC::getAlive() const
{
	return alive;
}

void NPC::loadNPC() {
	getHunt();
	df::Vector originalMapPos = mapPos;
	if (!loaded && (beingChased()))
	{
		setMapPos(df::Vector((float)(std::rand() % (DM.getHorizontal() - 32) + 26), (float)(std::rand() % (DM.getVertical() ) + 10)));
	}
	if (isHunting)
	{
		setMapPos(df::Vector((DM.getHorizontal() / 2) + ((float)(std::rand() % 5 - 2)), (DM.getVertical() / 2) + ((float)(std::rand() % 3 - 1))));
	}
	if (!loaded)
	{
		setPosition(mapPos);
	}
	else {
		setMapPos(originalMapPos);
	}
	loaded = true;
}

void NPC::unloadNPC() {
	if (loaded)
	{
		setMapPos(getPosition());
		//LM.writeLog("Stored pos: (%f, %f)\n", mapPos.getX(), mapPos.getY());
	}
	loaded = false;
	setPosition(df::Vector(-100, -100));
}

void NPC::checkHunt() 
{
	if (!isMurd)
	{	// If not murderer,
		return;
	}
	if (seen <= 0)
	{	// If player has seen too much ,
		murdTimer = -1;
		setHunt(true, true);
		return;
	}
	if (inLoadedRoom() && countNPCsInRoom() == 1)
	{	// If alone with player,
		murdTimer = -1;
		murdReaction = 45;
		if (murdWait > 0)
		{
			murdWait--;
		}
		if (murdWait == 0)
		{
			seen -= 5;
			setHunt(true, true);
		}
		return;
	} else if (inLoadedRoom() && getHunt() && countNPCsInRoom() >= 1) 
	{	// If caught while hunting,
		seen--;
		murdReaction--;
		murdTimer = -1;
		murdWait = 15;
		if (murdReaction > 0) {
			setHunt(true, false);
		}
		else {
			seen = 0;
			setHunt(true, true);
		}
		return;
	}
	else if (!inLoadedRoom() && countNPCsInRoom() == 2) {
		murdWait = std::rand() % 90 + 60;
		if (std::rand() % 2)
		{
			murdWait = -1;
		}
		murdReaction = 45;
		setHunt(true, false);
		return;
	}

	murdTimer = -1;
	murdWait = std::rand() % 90 + 60;
	if (std::rand() % 2)
	{
		murdWait = -1;
	}
	murdReaction = 45;
	setHunt(false, false);
}

void NPC::roam() {
	target = -1;
	if (patience <= -1) {
		patience = (std::rand() % 210) + 90;
		initPatience = patience;
	}

	if (patience != 0) {
		if (state == "idle" && stateCooldown > 0) {
			stateCooldown--;
			moving = false;
		}
		else if (state == "roaming" && stateCooldown > 0) {
			if (roamCooldown == 0) {
				df::Vector new_pos = df::Vector(mapPos.getX() + roamX, mapPos.getY() + roamY);
				if (new_pos.getY() > 5 && new_pos.getY() < DM.getVertical() - 5 && new_pos.getX() > 20 && new_pos.getX() < DM.getHorizontal() - 20) {
					mapPos.setXY(new_pos.getX(), new_pos.getY());
					WM.moveObject(this, mapPos);

					moving = true;

					if (roamX > 0)
					{
						faceRight = true;
					}
					if (roamX < 0)
					{
						faceRight = false;
					}
				}
				else {
					moving = false;
				}
				roamCooldown = 15;
			}
			roamCooldown--;
			stateCooldown--;
		}
		else {
			int choose = std::rand() % 2;
			if (choose == 0) {
				//LM.writeLog("Going into idle\n");
				state = "idle";
				stateCooldown = (std::rand() % 300) + 30;
				moving = false;
			}
			else if (choose == 1) {
				//LM.writeLog("Going into roam\n");
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

bool NPC::inLoadedRoom() const {
	Room* room = dynamic_cast<Room*>(WM.objectsOfType("room")[0]);
	return room->getCurrentPos() == roomPos;
}

int NPC::countNPCsInRoom() const
{
	int count = 0;
	df::ObjectList npcs = WM.objectsOfType("NPC");
	for (int i = 0; i < npcs.getCount(); i++)
	{
		NPC* npc = (NPC*)npcs[i];
		if (npc->getAlive() && npc->getRoomPos() == roomPos)
		{
			count++;
		}
	}
	return count;
}

bool NPC::beingChased() const
{
	df::ObjectList npcs = WM.objectsOfType("NPC");
	for (int i = 0; i < npcs.getCount(); i++)
	{
		NPC* npc = (NPC*)npcs[i];
		if (npc->isHunting && npc->getRoomPos() == roomPos)
		{
			return true;
		}
	}
	return false;
}

int NPC::eventHandler(const df::Event* p_e) {
	// if a step event occurs, call step
	if (p_e->getType() == df::STEP_EVENT) {
		step();
		return 1;
	}
	if (p_e->getType() == ROOM_LOADED_EVENT) {
		checkHunt();
		if (inLoadedRoom())
		{
			LM.writeLog("Loading NPC: roomPos %.0f, %.0f; mapPos %.0f, %.0f\n", roomPos.getX(), roomPos.getY(), mapPos.getX(), mapPos.getY());
			loadNPC();
		}
		else {
			LM.writeLog("Not loading NPC: roomPos %.0f, %.0f; mapPos %.0f, %.0f\n", roomPos.getX(), roomPos.getY(), mapPos.getX(), mapPos.getY());
			unloadNPC();
		}
		return 1;
	}
	return 0;
}

// Function that holds most of the AI logic. Does not include the logic for the murder yet
void NPC::step() {
	checkHunt();
	if (inLoadedRoom()) {
		loadNPC();
	}
	else {
		unloadNPC();
	}

	if (!alive)			// If NPC is dead,
	{
		return;	// Do nothing else
	}
	
	if (inLoadedRoom()) { // if the NPC is in the room with the player
		if (getHunt()) 
		{
			if (isHuntPlayer)
			{
				chasePlayer();
			}
			else {
				chaseNPC();
			}
		} 
		else if (beingChased())
		{
			leave(4, true);
		}
		else if (state != "leaving") { // if they are not set to leave,
			//setColor(df::GREEN);
			roam(); // have them roam around the room making either random movements or just idling
		}
		else {
			//setColor(df::RED);
			leave(); // if state is set to leave, have them find the nearest exit and go out that way
		}
	} else {
		if (getHunt())
		{
			assassinate();	// wait a bit then kill other npc in room
		}
		else {
			stall(); // wait around for a certain amount of time before deciding to go to a random adjacent room
		}
	}

	if (isHunting && inLoadedRoom()) {
		df::Vector playerPos = WM.objectsOfType("Player")[0]->getPosition();
		df::ObjectList npcs = WM.objectsOfType("NPC");
		if (abs(getPosition().getX() - playerPos.getX()) < 2 && 
			abs(getPosition().getY() - playerPos.getY()) < 2)
		{
			new Cutscene(1, getColor());
		}
		for (int i = 0; i < npcs.getCount(); i++)
		{
			NPC* npc = (NPC*)npcs[i];
			if (npc->getId() != getId() && npc->inLoadedRoom()  && 
				abs(getPosition().getX() - npc->getPosition().getX()) < 2 && 
				abs(getPosition().getY() - npc->getPosition().getY()) < 2)
			{
				npc->die();
			}
		}
	}
	patience--;
}

void NPC::stall() {
	target = -1;
	if (patience <= -1) {
		patience = (std::rand() % 210) + 90; // will wait between 3 - 10 seconds within a room
		initPatience = patience;
	}
	if (patience == initPatience - 60)
	{
		setMapPos(df::Vector((float)(std::rand() % (DM.getHorizontal() - 42) + 21), (float)(std::rand() % (DM.getVertical() - 10) + 5)));
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

		if (inLoadedRoom())
		{
			switch (roll) {
			case 0:	// West
				setMapPos(df::Vector((float)(DM.getHorizontal() - 21), (float)(DM.getVertical() / 2)));
				break;
			case 1:	// North
				setMapPos(df::Vector((float)(DM.getHorizontal() / 2), (float)(DM.getVertical() - 5)));
				break;
			case 2:	// East
				setMapPos(df::Vector((float)(21), (float)(DM.getVertical() / 2)));
				break;
			case 3:	// South
				setMapPos(df::Vector((float)(DM.getHorizontal() / 2), (float)(5)));
				break;
			}
		}
		else {
			setMapPos(df::Vector((float)(std::rand() % (DM.getHorizontal() - 42) + 21), (float)(std::rand() % (DM.getVertical() - 10) + 5)));
		}

		//LM.writeLog("Changing rooms to new room %f, %f\n", new_vec.getX(), new_vec.getY());
	}
}

void NPC::assassinate()
{
	if (murdTimer == -1)
	{
		murdTimer = std::rand() % 90 + 60;
	}
	murdTimer--;
	if (murdTimer == 0)
	{
		df::ObjectList npcs = WM.objectsOfType("NPC");
		for (int i = 0; i < npcs.getCount(); i++)
		{
			NPC* npc = (NPC*)npcs[i];
			if (npc->getId() != getId() && npc->getRoomPos() == roomPos)
			{
				npc->setMapPos(df::Vector((float)(std::rand() % (DM.getHorizontal() - 42) + 21), (float)(std::rand() % (DM.getVertical() - 10) + 5)));
				npc->die();
			}
		}
		// Move rooms

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

		if (inLoadedRoom())
		{
			switch (roll) {
			case 0:	// West
				setMapPos(df::Vector((float)(DM.getHorizontal() - 21), (float)(DM.getVertical() / 2)));
				break;
			case 1:	// North
				setMapPos(df::Vector((float)(DM.getHorizontal() / 2), (float)(DM.getVertical() - 5)));
				break;
			case 2:	// East
				setMapPos(df::Vector((float)(21), (float)(DM.getVertical() / 2)));
				break;
			case 3:	// South
				setMapPos(df::Vector((float)(DM.getHorizontal() / 2), (float)(5)));
				break;
			}
		}
		else {
			setMapPos(df::Vector((float)(std::rand() % (DM.getHorizontal() - 42) + 21), (float)(std::rand() % (DM.getVertical() - 10) + 5)));
		}
		setHunt(false, false);
		checkHunt();
	}
}

void NPC::leave(int speed, bool nearest) { // walk to a random exit of the room
	moving = true;
	patience = -1;
	df::Vector doorLocations[4];
	doorLocations[0] = df::Vector((float)(DM.getHorizontal() / 2), (float)(5));
	doorLocations[1] = df::Vector((float)(DM.getHorizontal() - 21), (float)(DM.getVertical() / 2));
	doorLocations[2] = df::Vector((float)(DM.getHorizontal() / 2), (float)(DM.getVertical() - 5));
	doorLocations[3] = df::Vector((float)(21), (float)(DM.getVertical() / 2));
	if (nearest)
	{
		int mindist = 9999;
		Room* room = (Room*)WM.objectsOfType("room")[0];
		bool* doors = room->getDoors();
		for (int i = 0; i < 4; i++)
		{
			int dist = (int)std::max(abs(doorLocations[i].getX() - getPosition().getX()),
								abs(doorLocations[i].getY() - getPosition().getY()));
			if (dist < mindist && doors[i])
			{
				mindist = dist;
				target = i;
			}
		}
	}
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
	df::Vector targetPos;
	switch (target) {
	case 0:	// Move to North
		targetPos = doorLocations[0];
		break;
	case 1:	// Move to East
		targetPos = doorLocations[1];
		break;
	case 2:	// Move to South
		targetPos = doorLocations[2];
		break;
	case 3:	// Move to West
		targetPos = doorLocations[3];
		break;
	}

	if (targetPos.getX() > getPosition().getX()) { // Find X roam
		roamX = 1;
	}
	else if (targetPos.getX() < getPosition().getX()) {
		roamX = -1;
	}
	else {
		roamX = 0;
	}

	if (targetPos.getY() > getPosition().getY()) { // Find Y roam
		roamY = 1;
	}
	else if (targetPos.getY() < getPosition().getY()) {
		roamY = -1;
	}
	else {
		roamY = 0;
	}

	if (roamX > 0)
	{
		faceRight = true;
	}
	if (roamX < 0)
	{
		faceRight = false;
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
		roamCooldown = speed;
		if (getMurd())
			LM.writeLog("RE: Leaving room\n");
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
			LM.writeLog("!!Err: OOB (In: Leave))!!\n");
		}
		roamCooldown = 15;
	}
	roamCooldown--;
}

void NPC::chaseNPC()
{
	moving = true;
	df::ObjectList npcs = WM.objectsOfType("NPC"); // Get NPCs
	NPC* target = nullptr;

	int mindist = 9999;
	for (int i = 0; i < npcs.getCount(); i++)
	{
		NPC* npc = (NPC*)npcs[i];
		int dist = (int)std::max(abs(npc->getPosition().getX() - getPosition().getX()),
			abs(npc->getPosition().getY() - getPosition().getY()));
		if (npc->getId() != getId() && npc->inLoadedRoom() && npc->getAlive() && dist < mindist) {
			mindist = dist;
			target = npc;
		}
	}

	if (target == nullptr)
	{	// If no suitable NPC found, attack player instead
		//chasePlayer();
		return;
	}
	df::Vector targetPos = target->getPosition(); // Get target position

	if (targetPos.getX() > getPosition().getX()) { // Find X roam
		roamX = 1;
	}
	else if (targetPos.getX() < getPosition().getX()) {
		roamX = -1;
	}
	else {
		roamX = 0;
	}

	if (targetPos.getY() > getPosition().getY()) { // Find Y roam
		roamY = 1;
	}
	else if (targetPos.getY() < getPosition().getY()) {
		roamY = -1;
	}
	else {
		roamY = 0;
	}

	if (roamX > 0)
	{
		faceRight = true;
	}
	if (roamX < 0)
	{
		faceRight = false;
	}

	if (roamCooldown == 0) {	// Roam towards NPC
		df::Vector new_pos = df::Vector(mapPos.getX() + roamX, mapPos.getY() + roamY);
		if (new_pos.getY() > 4 && new_pos.getY() < DM.getVertical() - 4 && new_pos.getX() > 20 && new_pos.getX() < DM.getHorizontal() - 20) {
			mapPos.setXY(new_pos.getX(), new_pos.getY());
			WM.moveObject(this, mapPos);
		}
		else {
			LM.writeLog("!!Err: OOB (In: Chase NPC)!!\n");
		}
		roamCooldown = std::rand() % 2 + 1;
	}
	roamCooldown--;
}

void NPC::chasePlayer()
{
	moving = true;
	df::Vector targetPos = WM.objectsOfType("Player")[0]->getPosition();	// Get player position

	if (targetPos.getX() > getPosition().getX()) { // Find X roam
		roamX = 1;
	}
	else if (targetPos.getX() < getPosition().getX()) {
		roamX = -1;
	}
	else {
		roamX = 0;
	}

	if (targetPos.getY() > getPosition().getY()) { // Find Y roam
		roamY = 1;
	}
	else if (targetPos.getY() < getPosition().getY()) {
		roamY = -1;
	}
	else {
		roamY = 0;
	}

	if (roamX > 0)
	{
		faceRight = true;
	}
	if (roamX < 0)
	{
		faceRight = false;
	}

	if (roamCooldown == 0) {	// Roam towards player
		df::Vector new_pos = df::Vector(mapPos.getX() + roamX, mapPos.getY() + roamY);
		if (new_pos.getY() > 4 && new_pos.getY() < DM.getVertical() - 4 && new_pos.getX() > 20 && new_pos.getX() < DM.getHorizontal() - 20) {
			mapPos.setXY(new_pos.getX(), new_pos.getY());
			WM.moveObject(this, mapPos);
		}
		else {
			LM.writeLog("!!Err: OOB (In: Chase Player)!!\n");
		}
		roamCooldown = 1;
	}
	roamCooldown--;
}

int NPC::draw()
{
	updateSprite();
	df::Sprite* p_s = RM.getSprite(getAnimation().getSprite()->getLabel());
	if (inLoadedRoom()) {
		if (beingChased() || isHunting)
		{
			if ((beingChased() && getAnimation().getSlowdownCount() == 0 && getAnimation().getIndex() % 3 == 0) ||
				(isHunting && getAnimation().getSlowdownCount() == 0 && getAnimation().getIndex() % 4 == 0))
			{
				RM.getSound("Run")->play();
			}
		}
		else if (moving && getAnimation().getSlowdownCount() == 0 && getAnimation().getIndex() % 4 == 0) {
			RM.getSound("Step")->play();
		}
	}

	p_s->setColor(color);
	return Object::draw();
}

df::Box NPC::getBox() const
{
	return df::Box(df::Vector(-2.5, -2.5), 5, 5);
}
