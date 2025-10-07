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
    // Load Player Sprites
    RM.loadSprite("sprites_dev/PCR_final.txt", "PC_right");
    RM.loadSprite("sprites_dev/PCL_final.txt", "PC_left");
    RM.loadSprite("sprites_dev/PC_walkR_final.txt", "PC_walk_right");
    RM.loadSprite("sprites_dev/PC_walkL_final.txt", "PC_walk_left");
    RM.loadSprite("sprites_dev/PC_shootR_final.txt", "PC_shoot_right");
    RM.loadSprite("sprites_dev/PC_shootL_final.txt", "PC_shoot_left");

    // Load NPC right idle sprites
    RM.loadSprite("sprites_dev/NPCR_final.txt", "NPC");
    RM.loadSprite("sprites_dev/NPCR_final.txt", "NPC_R");
    RM.getSprite("NPC_R")->setColor(df::RED);
    RM.loadSprite("sprites_dev/NPCR_final.txt", "NPC_G");
    RM.getSprite("NPC_G")->setColor(df::GREEN);
    RM.loadSprite("sprites_dev/NPCR_final.txt", "NPC_B");
    RM.getSprite("NPC_B")->setColor(df::BLUE);
    RM.loadSprite("sprites_dev/NPCR_final.txt", "NPC_C");
    RM.getSprite("NPC_C")->setColor(df::CYAN);
    RM.loadSprite("sprites_dev/NPCR_final.txt", "NPC_Y");
    RM.getSprite("NPC_Y")->setColor(df::YELLOW);
    RM.loadSprite("sprites_dev/NPCR_final.txt", "NPC_M");
    RM.getSprite("NPC_M")->setColor(df::MAGENTA);

    // Load NPC left idle sprites
    RM.loadSprite("sprites_dev/NPCL_final.txt", "NPC_left");
    RM.loadSprite("sprites_dev/NPCL_final.txt", "NPC_left_R");
    RM.getSprite("NPC_R")->setColor(df::RED);
    RM.loadSprite("sprites_dev/NPCL_final.txt", "NPC_left_G");
    RM.getSprite("NPC_G")->setColor(df::GREEN);
    RM.loadSprite("sprites_dev/NPCL_final.txt", "NPC_left_B");
    RM.getSprite("NPC_B")->setColor(df::BLUE);
    RM.loadSprite("sprites_dev/NPCL_final.txt", "NPC_left_C");
    RM.getSprite("NPC_C")->setColor(df::CYAN);
    RM.loadSprite("sprites_dev/NPCL_final.txt", "NPC_left_Y");
    RM.getSprite("NPC_Y")->setColor(df::YELLOW);
    RM.loadSprite("sprites_dev/NPCL_final.txt", "NPC_left_M");
    RM.getSprite("NPC_M")->setColor(df::MAGENTA);

    // Load NPC right roam sprites
    RM.loadSprite("sprites_dev/NPC_roamR_final.txt", "NPC_roam_right");
    RM.loadSprite("sprites_dev/NPC_roamR_final.txt", "NPC_roam_right_R");
    RM.getSprite("NPC_roam_right_R")->setColor(df::RED);
    RM.loadSprite("sprites_dev/NPC_roamR_final.txt", "NPC_roam_right_G");
    RM.getSprite("NPC_roam_right_G")->setColor(df::GREEN);
    RM.loadSprite("sprites_dev/NPC_roamR_final.txt", "NPC_roam_right_B");
    RM.getSprite("NPC_roam_right_B")->setColor(df::BLUE);
    RM.loadSprite("sprites_dev/NPC_roamR_final.txt", "NPC_roam_right_C");
    RM.getSprite("NPC_roam_right_C")->setColor(df::CYAN);
    RM.loadSprite("sprites_dev/NPC_roamR_final.txt", "NPC_roam_right_Y");
    RM.getSprite("NPC_roam_right_Y")->setColor(df::YELLOW);
    RM.loadSprite("sprites_dev/NPC_roamR_final.txt", "NPC_roam_right_M");
    RM.getSprite("NPC_roam_right_M")->setColor(df::MAGENTA);

    // load NPC left roam sprites
    RM.loadSprite("sprites_dev/NPC_roamL_final.txt", "NPC_roam_left");
    RM.loadSprite("sprites_dev/NPC_roamL_final.txt", "NPC_roam_left_R");
    RM.getSprite("NPC_roam_left_R")->setColor(df::RED);
    RM.loadSprite("sprites_dev/NPC_roamL_final.txt", "NPC_roam_left_G");
    RM.getSprite("NPC_roam_left_G")->setColor(df::GREEN);
    RM.loadSprite("sprites_dev/NPC_roamL_final.txt", "NPC_roam_left_B");
    RM.getSprite("NPC_roam_left_B")->setColor(df::BLUE);
    RM.loadSprite("sprites_dev/NPC_roamL_final.txt", "NPC_roam_left_C");
    RM.getSprite("NPC_roam_left_C")->setColor(df::CYAN);
    RM.loadSprite("sprites_dev/NPC_roamL_final.txt", "NPC_roam_left_Y");
    RM.getSprite("NPC_roam_left_Y")->setColor(df::YELLOW);
    RM.loadSprite("sprites_dev/NPC_roamL_final.txt", "NPC_roam_left_M");
    RM.getSprite("NPC_roam_left_M")->setColor(df::MAGENTA);

    // Load NPC right panic sprites
    RM.loadSprite("sprites_dev/NPC_panicR_final.txt", "NPC_panic_right");
    RM.loadSprite("sprites_dev/NPC_panicR_final.txt", "NPC_panic_right_R");
    RM.getSprite("NPC_panic_right_R")->setColor(df::RED);
    RM.loadSprite("sprites_dev/NPC_panicR_final.txt", "NPC_panic_right_G");
    RM.getSprite("NPC_panic_right_G")->setColor(df::GREEN);
    RM.loadSprite("sprites_dev/NPC_panicR_final.txt", "NPC_panic_right_B");
    RM.getSprite("NPC_panic_right_B")->setColor(df::BLUE);
    RM.loadSprite("sprites_dev/NPC_panicR_final.txt", "NPC_panic_right_C");
    RM.getSprite("NPC_panic_right_C")->setColor(df::CYAN);
    RM.loadSprite("sprites_dev/NPC_panicR_final.txt", "NPC_panic_right_Y");
    RM.getSprite("NPC_panic_right_Y")->setColor(df::YELLOW);
    RM.loadSprite("sprites_dev/NPC_panicR_final.txt", "NPC_panic_right_M");
    RM.getSprite("NPC_panic_right_M")->setColor(df::MAGENTA);

    // Load NPC left panic sprites
    RM.loadSprite("sprites_dev/NPC_panicL_final.txt", "NPC_panic_left");
    RM.loadSprite("sprites_dev/NPC_panicL_final.txt", "NPC_panic_left_R");
    RM.getSprite("NPC_panic_left_R")->setColor(df::RED);
    RM.loadSprite("sprites_dev/NPC_panicL_final.txt", "NPC_panic_left_G");
    RM.getSprite("NPC_panic_left_G")->setColor(df::GREEN);
    RM.loadSprite("sprites_dev/NPC_panicL_final.txt", "NPC_panic_left_B");
    RM.getSprite("NPC_panic_left_B")->setColor(df::BLUE);
    RM.loadSprite("sprites_dev/NPC_panicL_final.txt", "NPC_panic_left_C");
    RM.getSprite("NPC_panic_left_C")->setColor(df::CYAN);
    RM.loadSprite("sprites_dev/NPC_panicL_final.txt", "NPC_panic_left_Y");
    RM.getSprite("NPC_panic_left_Y")->setColor(df::YELLOW);
    RM.loadSprite("sprites_dev/NPC_panicL_final.txt", "NPC_panic_left_M");
    RM.getSprite("NPC_panic_left_M")->setColor(df::MAGENTA);

    // Load right murder sprites
    RM.loadSprite("sprites_dev/MurdR_final.txt", "Murd");
    RM.loadSprite("sprites_dev/MurdR_final.txt", "Murd_R");
    RM.getSprite("Murd_R")->setColor(df::RED);
    RM.loadSprite("sprites_dev/MurdR_final.txt", "Murd_G");
    RM.getSprite("Murd_G")->setColor(df::GREEN);
    RM.loadSprite("sprites_dev/MurdR_final.txt", "Murd_B");
    RM.getSprite("Murd_B")->setColor(df::BLUE);
    RM.loadSprite("sprites_dev/MurdR_final.txt", "Murd_C");
    RM.getSprite("Murd_C")->setColor(df::CYAN);
    RM.loadSprite("sprites_dev/MurdR_final.txt", "Murd_Y");
    RM.getSprite("Murd_Y")->setColor(df::YELLOW);
    RM.loadSprite("sprites_dev/MurdR_final.txt", "Murd_M");
    RM.getSprite("Murd_M")->setColor(df::MAGENTA);

    // Load left murder sprites
    RM.loadSprite("sprites_dev/MurdL_final.txt", "Murd_left");
    RM.loadSprite("sprites_dev/MurdL_final.txt", "Murd_left_R");
    RM.getSprite("Murd_left_R")->setColor(df::RED);
    RM.loadSprite("sprites_dev/MurdL_final.txt", "Murd_left_G");
    RM.getSprite("Murd_left_G")->setColor(df::GREEN);
    RM.loadSprite("sprites_dev/MurdL_final.txt", "Murd_left_B");
    RM.getSprite("Murd_left_B")->setColor(df::BLUE);
    RM.loadSprite("sprites_dev/MurdL_final.txt", "Murd_left_C");
    RM.getSprite("Murd_left_C")->setColor(df::CYAN);
    RM.loadSprite("sprites_dev/MurdL_final.txt", "Murd_left_Y");
    RM.getSprite("Murd_left_Y")->setColor(df::YELLOW);
    RM.loadSprite("sprites_dev/MurdL_final.txt", "Murd_left_M");
    RM.getSprite("Murd_left_M")->setColor(df::MAGENTA);

    // Load NPC Death sprites
    RM.loadSprite("sprites_dev/Dead_final.txt", "Dead");
    RM.loadSprite("sprites_dev/Dead_final.txt", "Dead_R");
    RM.getSprite("Dead_R")->setColor(df::RED);
    RM.loadSprite("sprites_dev/Dead_final.txt", "Dead_G");
    RM.getSprite("Dead_G")->setColor(df::GREEN);
    RM.loadSprite("sprites_dev/Dead_final.txt", "Dead_B");
    RM.getSprite("Dead_B")->setColor(df::BLUE);
    RM.loadSprite("sprites_dev/Dead_final.txt", "Dead_C");
    RM.getSprite("Dead_C")->setColor(df::CYAN);
    RM.loadSprite("sprites_dev/Dead_final.txt", "Dead_Y");
    RM.getSprite("Dead_Y")->setColor(df::YELLOW);
    RM.loadSprite("sprites_dev/Dead_final.txt", "Dead_M");
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
    RM.loadSprite("sprites_dev/Room_Wall_B_NoDoor_dev.txt", "Room_W_N");
    RM.loadSprite("sprites_dev/Room_Wall_B_Door_dev.txt", "Room_W_D");


    RM.loadSprite("sprites_dev/Bingus.txt", "Bingus");
    RM.loadSprite("sprites_dev/Death_Screen_dev.txt", "Death");
    RM.loadSprite("sprites_dev/Win_Screen_dev.txt", "Win");
    RM.loadSprite("sprites_dev/Innocent_Death_Screen_dev.txt", "Murderer");
    RM.loadSprite("sprites_dev/GameOver_dev.txt", "End");
    RM.loadSprite("sprites_dev/Bullet_dev.txt", "Bullet");

    RM.loadSprite("sprites/Cutscene_Death.txt", "Death_Cutscene");
    RM.loadSprite("sprites/Cutscene_Win.txt", "Win_Cutscene");
    RM.loadSprite("sprites/Cutscene_Inno.txt", "Inno_Cutscene");
}

// Populate world with some objects.
void populateWorld() {
    // Load Sounds
    RM.loadSound("sounds_dev/Sound1_dev.wav", "Sound1");
    RM.loadSound("sounds_dev/Sound2_dev.wav", "Sound2");
    RM.loadSound("sounds_dev/Sound3_dev.wav", "Sound3");

    // Load Music
    RM.loadMusic("sounds/Backing Track.wav", "Music");

    new GameStart;
    RM.getMusic("Music")->play();
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


