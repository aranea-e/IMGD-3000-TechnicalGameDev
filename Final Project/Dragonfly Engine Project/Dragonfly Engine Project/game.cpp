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

    // Load new Room Sprites
    RM.loadSprite("sprites/Room_Foyer.txt", "Room_00");
    RM.loadSprite("sprites/Room_Kitchen.txt", "Room_10");
    RM.loadSprite("sprites/Room_Diningroom.txt", "Room_20");
    RM.loadSprite("sprites/Room_Bedroom.txt", "Room_30");
    RM.loadSprite("sprites/Room_Bathroom.txt", "Room_01");
    RM.loadSprite("sprites/Room_Billiards.txt", "Room_11");
    RM.loadSprite("sprites/Room_Ballroom.txt", "Room_21");
    RM.loadSprite("sprites/Room_MasterBathroom.txt", "Room_31");
    RM.loadSprite("sprites/Room_Pool.txt", "Room_02");
    RM.loadSprite("sprites/Room_Living.txt", "Room_12");
    RM.loadSprite("sprites/Room_Library.txt", "Room_22");
    RM.loadSprite("sprites/Room_Masters.txt", "Room_32");
    RM.loadSprite("sprites/Room_Backyard1.txt", "Room_03");
    RM.loadSprite("sprites/Room_Backyard2.txt", "Room_13");
    RM.loadSprite("sprites/Room_Greenhouse.txt", "Room_23");
    RM.loadSprite("sprites/Room_Laundry.txt", "Room_33");

    RM.loadSprite("sprites/Room_Wall_B_NoDoor.txt", "Room_W_N");
    RM.loadSprite("sprites/Room_Wall_B_Door.txt", "Room_W_D");


    RM.loadSprite("sprites/Bingus.txt", "Bingus");
    RM.loadSprite("sprites/Death_Screen.txt", "Death");
    RM.loadSprite("sprites/Win_Screen.txt", "Win");
    RM.loadSprite("sprites/Innocent_Death_Screen.txt", "Murderer");
    RM.loadSprite("sprites/GameOver.txt", "End");
    RM.loadSprite("sprites/Bullet.txt", "Bullet");

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
    // Load Sounds
    RM.loadSound("sounds/start.wav", "Start");
    RM.loadSound("sounds/step.wav", "Step");
    RM.loadSound("sounds/run.wav", "Run");
    RM.loadSound("sounds/clue.wav", "Clue");
    RM.loadSound("sounds/shot.wav", "Shot");
    RM.loadSound("sounds/npc_death.wav", "NPC_Death");
    RM.loadSound("sounds/npc_shot.wav", "NPC_Shot");
    RM.loadSound("sounds/player_death.wav", "Player_Death");
    RM.loadSound("sounds/win.wav", "Win");
    RM.loadSound("sounds/loss.wav", "Loss");

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


