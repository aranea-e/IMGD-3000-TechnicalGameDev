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
    // Load Dev Character Sprites
    //RM.loadSprite("sprites_dev/PC_dev.txt", "PC");
    //RM.loadSprite("sprites_dev/NPC_dev.txt", "NPC");
    RM.loadSprite("sprites_dev/Murd_dev.txt", "Murd");
    //RM.loadSprite("sprites_dev/Dead_dev.txt", "Dead");

    // Load PC Sprites
    RM.loadSprite("sprites/PCL_final.txt", "PC_L");
    RM.loadSprite("sprites/PCR_final.txt", "PC_R");
    RM.loadSprite("sprites/PC_walkL_final.txt", "PCw_L");
    RM.loadSprite("sprites/PC_walkR_final.txt", "PCw_R");
    RM.loadSprite("sprites/PC_shootL_final.txt", "PCs_L");
    RM.loadSprite("sprites/PC_shootR_final.txt", "PCs_R");

    // Load NPC Sprites
    RM.loadSprite("sprites/NPCL_final.txt", "NPC_L");
    RM.loadSprite("sprites/NPCR_final.txt", "NPC_R");
    RM.loadSprite("sprites/NPC_roamL_final.txt", "NPCw_L");
    RM.loadSprite("sprites/NPC_roamR_final.txt", "NPCw_R");
    RM.loadSprite("sprites/NPC_panicL_final.txt", "NPCp_L");
    RM.loadSprite("sprites/NPC_panicR_final.txt", "NPCp_R");
    RM.loadSprite("sprites/Dead_final.txt", "Dead");

    // Load Murderer Sprites
    RM.loadSprite("sprites/MurdL_final.txt", "Murd_L");
    RM.loadSprite("sprites/MurdR_final.txt", "Murd_R");

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

    RM.loadSprite("sprites/Clue_H.txt", "Clue_H");
    RM.loadSprite("sprites/Clue_V.txt", "Clue_V");
    RM.loadSprite("sprites/Clue_Final.txt", "Clue_Final");

    RM.loadSprite("sprites/Search_Cursor.txt", "Search_Cursor");
}

// Populate world with some objects.
void populateWorld() {
    // Load Soundsddddddd
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


