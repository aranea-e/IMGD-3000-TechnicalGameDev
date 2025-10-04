#include "GameStart.h"
#include "Reticle.h"
#include "Room.h"
#include "Player.h"

GameStart::GameStart() {
	start();
}

void GameStart::start() {
	new Room;
	new Reticle;
	new Player;
}