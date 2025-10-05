#include "NPC.h"
#include "DisplayManager.h"
#include <cstdlib>
#include "WorldManager.h"
#include "Room.h"
#include "EventStep.h"
#include "LogManager.h"

NPC::NPC() : NPC(df::WHITE) { }

NPC::NPC(df::Color npc_color)
{

    roomPos = df::Vector(0, 1);
    mapPos = df::Vector(DM.getHorizontal() / 2, DM.getVertical() / 2);
    patience = -1;
    stateCooldown = 0;
    roamCooldown = 0;
    state = "idle";
    roamX = 0;
    roamY = 0;

    // set sprite
    setColor(npc_color);
    // set type
    setType("NPC");

    setSolidness(df::SOFT);
    setAltitude(1);

    if (inLoadedRoom()) {
        loadNPC();
    }
    else {
        unloadNPC();
    }
}

void NPC::setColor(df::Color npc_color) {
    switch (npc_color) {
    case df::RED:
        setSprite("NPC_R");
        break;
    case df::GREEN:
        setSprite("NPC_G");
        break;
    case df::BLUE:
        setSprite("NPC_B");
        break;
    case df::CYAN:
        setSprite("NPC_C");
        break;
    case df::YELLOW:
        setSprite("NPC_Y");
        break;
    case df::MAGENTA:
        setSprite("NPC_M");
        break;
    case df::WHITE:
    default:
        setSprite("NPC");
    }
}

void NPC::setRoomPos(df::Vector new_room) {
	roomPos = new_room;
}

df::Vector NPC::getRoomPos() {
	return roomPos;
}

void NPC::loadNPC() {
    setPosition(mapPos);
}

void NPC::unloadNPC() {
    setPosition(df::Vector(- 100, -100));
}

void NPC::roam() {
    if (patience <= -1) {
        patience = (std::rand() % 2400) + 600;
    }

    if (patience != 0) {
        if (state == "idle" && stateCooldown > 0) {
            stateCooldown--;
        }
        else if (state == "roaming" && stateCooldown > 0) {
            if (roamCooldown == 0) {
                df::Vector new_pos = df::Vector(mapPos.getX() + roamX, mapPos.getY() + roamY);
                if (new_pos.getY() > 5 && new_pos.getY() < DM.getVertical() - 5 && new_pos.getX() > 20 && new_pos.getX() < DM.getHorizontal() - 20) {
                    mapPos.setXY(new_pos.getX(), new_pos.getY());
                    WM.moveObject(this, mapPos);
                }
                roamCooldown = 15;
            }
            roamCooldown--;
            stateCooldown--;
        }
        else {
            int choose = std::rand() % 2;
            if (choose == 0) {
                LM.writeLog("Going into idle\n");
                state = "idle";
                stateCooldown = (std::rand() % 300) + 30;
            }
            else if (choose == 1) {
                LM.writeLog("Going into roam\n");
                state = "roaming";
                stateCooldown = (std::rand() % 300) + 30;
                roamX = (std::rand() % 3) - 1;
                roamY = (std::rand() % 3) - 1;
            }
        }
    }
    else {
        state = "leaving";
    }
}

bool NPC::inLoadedRoom() {
    Room* room = dynamic_cast<Room*>(WM.objectsOfType("room")[0]);
    return room->getCurrentPos() == roomPos;
}

int NPC::eventHandler(const df::Event* p_e) {
    // if a step event occurs, call step
    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }
    return 0;
}

// Function that holds most of the AI logic. Does not include the logic for the murder yet
void NPC::step() {
    if (inLoadedRoom()) { // if the NPC is in the room with the player
        loadNPC(); // Load NPC at their room position
        if (state != "leaving") { // if they are not set to leave,
            roam(); // have them roam around the room making either random movements or just idling
        }
        else {
            leave(); // if state is set to leave, have them find the nearest exit and go out that way
        }
    }
    else {
        unloadNPC(); // Move the NPC to a position off screen while still presevering where their room position is
        stall(); // wait around for a certain amount of time before deciding to go to a random adjacent room
    }
    patience--;
}

void NPC::stall() {
    if (patience <= -1) {
        patience = (std::rand() % 2400) + 600; // will wait between 2 - 10 seconds within a room
    }

    if (patience == 0) {
        int roll = std::rand() % 4;
        int x_move = (1 - (roll % 2)) * (roll - 1); // if roll = 0, move to the left; if roll = 2, move to the right
        int y_move = (roll % 2) * (roll - 2); // if roll = 1, move to the left; if roll = 3, move to the right
        df::Vector new_vec = df::Vector(roomPos.getX() + x_move, roomPos.getY() + y_move);
        while (new_vec.getX() < 0 || new_vec.getX() > 3 || new_vec.getY() < 0 || new_vec.getY() > 3) {
            roll = std::rand() % 4;
            x_move = x_move = (1 - (roll % 2)) * (roll - 1);
            y_move = y_move = (roll % 2) * (roll - 2);
            new_vec.setXY(roomPos.getX() + x_move, roomPos.getY() + y_move);
        }
        setRoomPos(new_vec);
        LM.writeLog("Changing rooms to new room %f, %f", new_vec.getX(), new_vec.getY());
    }
}

void NPC::leave() { // walk to a random exit of the room

}