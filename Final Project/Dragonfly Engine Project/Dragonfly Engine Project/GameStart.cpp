#include "GameStart.h"
#include "Reticle.h"
#include "Room.h"
#include "Player.h"
#include "NPC.h"
#include "DisplayManager.h"
#include "WorldManager.h"

GameStart::GameStart() {
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
		return 1;
	}
	return 0;
}

void GameStart::start() {
	new Room;
	new Reticle;
	new Player;
	new NPC;
}