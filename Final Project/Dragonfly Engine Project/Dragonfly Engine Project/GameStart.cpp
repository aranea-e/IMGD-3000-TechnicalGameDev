#include "GameStart.h"
#include "Reticle.h"
#include "Room.h"

GameStart::GameStart() {
	start();
}

void GameStart::start() {
	new Room(df::Vector(3, 3));
	new Reticle;
}