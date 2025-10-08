#include "GameStart.h"
#include "Reticle.h"
#include "Room.h"
#include "Player.h"
#include "NPC.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "LogManager.h"
#include "GameEnd.h"
#include "Clue.h"
#include "ResourceManager.h"

GameStart::GameStart() {
	setSolidness(df::SPECTRAL);
	setSprite("Bingus");
	df::Vector p(DM.getHorizontal() / 2, DM.getVertical() / 2);
	setPosition(p);
}

int GameStart::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		if (p_keyboard_event->getKey() == df::Keyboard::P) {
			start();
			WM.markForDelete(this);
		}
		if (p_keyboard_event->getKey() == df::Keyboard::Q) {
			new GameEnd(3);
		}
		return 1;
	}
	return 0;
}

void GameStart::start() {
	df::ObjectList objs = WM.getAllObjects();
	for (int i = 0; i < objs.getCount(); i++)
	{
		WM.markForDelete(objs[i]);
	}

	new Room;
	new Reticle;
	new Player;
	new NPC(df::RED, df::Vector(1, 1));
	new NPC(df::BLUE, df::Vector(1, 1));
	new NPC(df::GREEN, df::Vector(1, 1));
	new NPC(df::CYAN, df::Vector(2, 2));
	new NPC(df::YELLOW, df::Vector(2, 2));
	new NPC(df::MAGENTA, df::Vector(2, 2));
	new Clue;

	RM.getSound("Start")->play();

	//NPC* murd = (NPC*)WM.objectsOfType("NPC")[0];
	

	bool isMurd = false;
	while (!isMurd) {
		NPC* murd = (NPC*)WM.objectsOfType("NPC")[std::rand() % 6];
		murd->setMurd();

		df::ObjectList npcs = WM.objectsOfType("NPC");
		for (size_t i = 0; i < 6; i++)
		{
			NPC* npc = (NPC*)npcs[i];
			if (npc->getMurd())
			{
				isMurd = true;
			}
		}
	}
}