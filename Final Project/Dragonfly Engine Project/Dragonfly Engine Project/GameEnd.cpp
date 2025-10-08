#include "GameEnd.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameStart.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "Room.h"
#include "Reticle.h"
#include "Player.h"
#include "NPC.h"
#include "GameManager.h"
#include "Windows.h"
#include "Clue.h"

GameEnd::GameEnd(int type)
{
	setSolidness(df::SPECTRAL);
	m_type = type;
	df::Vector p(DM.getHorizontal() / 2, DM.getVertical() / 2);
	setPosition(p);
	setType("GameEnd");
	end();
}

int GameEnd::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		const df::EventKeyboard* p_keyboard_event =
			dynamic_cast <const df::EventKeyboard*> (p_e);
		if (p_keyboard_event->getKey() == df::Keyboard::P) {
			restart();
			WM.markForDelete(this);
		}
		if (p_keyboard_event->getKey() == df::Keyboard::Q) {
			WM.markForDelete(this);
			new GameEnd(3);
		}
		if (p_keyboard_event->getKey() == df::Keyboard::R) {
			new GameStart();
			WM.markForDelete(this);
		}
		return 1;
	}
	return 0;
}

void GameEnd::restart() {
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

	NPC* murd = (NPC*)WM.objectsOfType("NPC")[std::rand() % 6];
	murd->setMurd();
}

void GameEnd::end() {
	df::ObjectList object_list = WM.getAllObjects();
	for (int i = 0; i < object_list.getCount(); i++) {
		df::Object* p_o = object_list[i];
		if (p_o->getType() != "GameEnd")
		{
			WM.markForDelete(p_o);
		}
	}

	switch (m_type) {
	case 0:
		RM.getSound("Win")->play();
		setSprite("Win");
		LM.writeLog("Game End: Player Won\n");
		break;
	case 1:
		RM.getSound("Player_Death")->play();
		setSprite("Death");
		LM.writeLog("Game End: Player Killed\n");
		break;
	case 2:
		RM.getSound("Loss")->play();
		setSprite("Murderer");
		LM.writeLog("Game End: Player Shot Innocent\n");
		break;
	case 3:
		setSprite("End");
		LM.writeLog("Game End: Player Quit\n");
		WM.update();
		WM.draw();
		DM.swapBuffers();
		Sleep(3000);
		GM.setGameOver();
		break;
	}

	//new GameStart;
}