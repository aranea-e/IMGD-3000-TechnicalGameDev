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

GameEnd::GameEnd(int type)
{
	m_type = type;
	df::Vector p(DM.getHorizontal() / 2, DM.getVertical() / 2);
	setPosition(p);
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
			m_type = 3;
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
	new Room;
	new Reticle;
	new Player;
	new NPC(df::RED, df::Vector(1, 1));
	new NPC(df::BLUE, df::Vector(1, 1));
	new NPC(df::GREEN, df::Vector(1, 1));
	new NPC(df::CYAN, df::Vector(2, 2));
	new NPC(df::YELLOW, df::Vector(2, 2));
	new NPC(df::MAGENTA, df::Vector(2, 2));

	NPC* murd = (NPC*)WM.objectsOfType("NPC")[std::rand() % 6];
	murd->setMurd();
}

void GameEnd::end() {
	df::ObjectList object_list = WM.getAllObjects();
	for (int i = 0; i < object_list.getCount(); i++) {
		df::Object* p_o = object_list[i];
		WM.markForDelete(p_o);
	}

	switch (m_type) {
	case 0:
		RM.getSound("Sound1")->play();
		setSprite("Win");
		LM.writeLog("Game End: Player Won\n");
		break;
	case 1:
		RM.getSound("Sound2")->play();
		setSprite("Death");
		LM.writeLog("Game End: Player Killed\n");
		break;
	case 2:
		RM.getSound("Sound3")->play();
		setSprite("Murderer");
		LM.writeLog("Game End: Player Shot Innocent\n");
		break;
	case 3:
		setSprite("End");
		LM.writeLog("Game End: Player Quit\n");
		Sleep(5000);
		GM.setGameOver();
		break;
	}

	//new GameStart;
}