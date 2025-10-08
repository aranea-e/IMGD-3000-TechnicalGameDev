#include "Clue.h"
#include "WorldManager.h"
#include "Room.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "NPC.h"
#include "EventSearch.h"
#include <algorithm>
#include "Player.h"
#include "ResourceManager.h"

Clue::Clue()
{
	LM.writeLog("Spawned Clues\n");
	setPosition(df::Vector(DM.getHorizontal() / 2, DM.getVertical() / 2));
	setSolidness(df::SPECTRAL);
	positions = new df::Vector[6];
	for (int i = 0; i < 6; i++)
	{
		positions[i] = df::Vector(-1, -1);
	}
	//LM.setFlush(true);
	for (int i = 0; i < 6; i++)
	{
		df::Vector* pos = new df::Vector((int)(std::rand() % 4), (int)(std::rand() % 4));
		while (isRoomTaken(*pos)) {
			delete(pos);
			pos = new df::Vector((int)(std::rand() % 4), (int)(std::rand() % 4));
			//LM.writeLog("Taken Pos: (%f, %f)\n", pos->getX(), pos->getY());
		}
		positions[i] = *pos;
		LM.writeLog("Clue %d: (%f, %f)\n", i, pos->getX(), pos->getY());
	}
	//LM.setFlush(false);

	revealed = new bool[6] {false};
	//for (int i = 0; i < 6; i++)
	//{
	//	revealed[i] = true;
	//}
}

int Clue::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == SEARCH_EVENT)
	{
		search();
	}
	return 0;
}

bool Clue::isRoomTaken(df::Vector room) const {
	for (int i = 0; i < 6; i++)
	{
		if (positions[i] == room)
		{
			return true;
		}
	}
	return false;
}

int Clue::inLoadedRoom() const {
	Room* room = dynamic_cast<Room*>(WM.objectsOfType("room")[0]);
	for (int i = 0; i < 6; i++)
	{
		if (room->getCurrentPos() == positions[i]) {
			return i;
		}
	}
	return -1;
}

int Clue::draw()
{
	int index = 0;
	if (inLoadedRoom() == -1)
	{
		return 0;
	}
	df::Color c;
	if (inLoadedRoom() > 2)
	{
		c = df::BLUE;
	}
	else {
		c = df::RED;
	}
	switch (inLoadedRoom() % 3) {
	case 0:
		setSprite("Clue_H");
		if (inLoadedRoom() == 0 && revealed[0])
		{
			index = positions[2].getY() + 1;
		}
		if (inLoadedRoom() == 3 && revealed[3])
		{
			index = positions[5].getY() + 1;
		}
		break;
	case 1:
		setSprite("Clue_V");
		if (inLoadedRoom() == 1 && revealed[1])
		{
			index = positions[2].getX() + 1;
		}
		if (inLoadedRoom() == 4 && revealed[4])
		{
			index = positions[5].getX() + 1;
		}
		break;
	case 2:
		setSprite("Clue_Final");
		if (inLoadedRoom() == 2 && !(revealed[0] && revealed[1]) && !revealed[2])
		{
			return 0;
		}
		if (inLoadedRoom() == 2 && revealed[2])
		{
			switch (getMurdColor()) {
			case df::RED:
			case df::BLUE:
			case df::GREEN:
				index = 1;
				break;
			case df::CYAN:
			case df::MAGENTA:
			case df::YELLOW:
				index = 2;
				break;
			}
		}
		if (inLoadedRoom() == 5 && !(revealed[3] && revealed[4]) && !revealed[5])
		{
			return 0;
		}
		if (inLoadedRoom() == 5 && revealed[5])
		{
			switch (getMurdColor()) {
			case df::RED:
			case df::MAGENTA:
			case df::YELLOW:
				index = 3;
				break;
			case df::CYAN:
			case df::BLUE:
			case df::GREEN:
				index = 4;
				break;
			}
		}
		break;
	}
	getAnimation().getSprite()->setColor(c);
	getAnimation().getSprite()->draw(index, getPosition());
	return 0;
}

df::Color Clue::getMurdColor() const
{
	df::ObjectList npcs = WM.objectsOfType("NPC");
	for (size_t i = 0; i < 6; i++)
	{
		NPC* npc = (NPC*)npcs[i];
		if (npc->getMurd())
		{
			return npc->getColor();
		}
	}
	return df::UNDEFINED_COLOR;
}

void Clue::search()
{
	Player* p_p = (Player*)WM.objectsOfType("Player")[0];
	float dist = std::max(std::abs(getPosition().getX() - p_p->getPosition().getX()),
						  1 + std::abs(getPosition().getY() - p_p->getPosition().getY()));
	if (dist < 5 && inLoadedRoom() != -1)
	{
		if (!revealed[inLoadedRoom()])
			RM.getSound("Clue")->play();
		revealed[inLoadedRoom()] = true;
	}
}
