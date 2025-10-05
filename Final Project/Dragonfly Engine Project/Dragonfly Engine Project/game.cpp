//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"

// Game includes.
#include "GameStart.h"

void loadResources(void) {
    // Load Character Sprites
    RM.loadSprite("sprites_dev/PC_dev.txt", "PC");
    RM.loadSprite("sprites_dev/NPC_dev.txt", "NPC");
    RM.loadSprite("sprites_dev/NPC_dev.txt", "NPC_R");
    RM.getSprite("NPC_R")->setColor(df::RED);
    RM.loadSprite("sprites_dev/NPC_dev.txt", "NPC_G");
    RM.getSprite("NPC_G")->setColor(df::GREEN);
    RM.loadSprite("sprites_dev/NPC_dev.txt", "NPC_B");
    RM.getSprite("NPC_B")->setColor(df::BLUE);
    RM.loadSprite("sprites_dev/NPC_dev.txt", "NPC_C");
    RM.getSprite("NPC_C")->setColor(df::CYAN);
    RM.loadSprite("sprites_dev/NPC_dev.txt", "NPC_Y");
    RM.getSprite("NPC_Y")->setColor(df::YELLOW);
    RM.loadSprite("sprites_dev/NPC_dev.txt", "NPC_M");
    RM.getSprite("NPC_M")->setColor(df::MAGENTA);

    RM.loadSprite("sprites_dev/Murd_dev.txt", "Murd");
    RM.loadSprite("sprites_dev/Murd_dev.txt", "Murd_R");
    RM.getSprite("Murd_R")->setColor(df::RED);
    RM.loadSprite("sprites_dev/Murd_dev.txt", "Murd_G");
    RM.getSprite("Murd_G")->setColor(df::GREEN);
    RM.loadSprite("sprites_dev/Murd_dev.txt", "Murd_B");
    RM.getSprite("Murd_B")->setColor(df::BLUE);
    RM.loadSprite("sprites_dev/Murd_dev.txt", "Murd_C");
    RM.getSprite("Murd_C")->setColor(df::CYAN);
    RM.loadSprite("sprites_dev/Murd_dev.txt", "Murd_Y");
    RM.getSprite("Murd_Y")->setColor(df::YELLOW);
    RM.loadSprite("sprites_dev/Murd_dev.txt", "Murd_M");
    RM.getSprite("Murd_M")->setColor(df::MAGENTA);

    RM.loadSprite("sprites_dev/Dead_dev.txt", "Dead");
    RM.loadSprite("sprites_dev/Dead_dev.txt", "Dead_R");
    RM.getSprite("Dead_R")->setColor(df::RED);
    RM.loadSprite("sprites_dev/Dead_dev.txt", "Dead_G");
    RM.getSprite("Dead_G")->setColor(df::GREEN);
    RM.loadSprite("sprites_dev/Dead_dev.txt", "Dead_B");
    RM.getSprite("Dead_B")->setColor(df::BLUE);
    RM.loadSprite("sprites_dev/Dead_dev.txt", "Dead_C");
    RM.getSprite("Dead_C")->setColor(df::CYAN);
    RM.loadSprite("sprites_dev/Dead_dev.txt", "Dead_Y");
    RM.getSprite("Dead_Y")->setColor(df::YELLOW);
    RM.loadSprite("sprites_dev/Dead_dev.txt", "Dead_M");
    RM.getSprite("Dead_M")->setColor(df::MAGENTA);

    // Load Room Sprites.
    RM.loadSprite("sprites_dev/Room_BL_dev.txt", "Room_BL");
    RM.loadSprite("sprites_dev/Room_BM_dev.txt", "Room_BM");
    RM.loadSprite("sprites_dev/Room_BR_dev.txt", "Room_BR");
    RM.loadSprite("sprites_dev/Room_ML_dev.txt", "Room_ML");
    RM.loadSprite("sprites_dev/Room_MM_dev.txt", "Room_MM");
    RM.loadSprite("sprites_dev/Room_MR_dev.txt", "Room_MR");
    RM.loadSprite("sprites_dev/Room_TL_dev.txt", "Room_TL");
    RM.loadSprite("sprites_dev/Room_TM_dev.txt", "Room_TM");
    RM.loadSprite("sprites_dev/Room_TR_dev.txt", "Room_TR");

    RM.loadSprite("sprites_dev/Bingus.txt", "Bingus");
    RM.loadSprite("sprites_dev/Bullet_dev.txt", "Bullet");
}

// Populate world with some objects.
void populateWorld() {
    // Load Sounds
    RM.loadSound("sounds_dev/Sound1_dev.wav", "Sound1");
    RM.loadSound("sounds_dev/Sound2_dev.wav", "Sound2");
    RM.loadSound("sounds_dev/Sound3_dev.wav", "Sound3");

    // Load Music
    //RM.loadMusic("filepath", "musicname");

    new GameStart;
}

int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp() != 0)  {
    LM.writeLog("Error starting game manager!");
    return -1;
  }

  // Load game resources.
  loadResources();

  // Populate game world with some objects.
  populateWorld();

  GM.run();

  // Shut everything down.
  GM.shutDown();

  // All is well.
  return 0;
}


