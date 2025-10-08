#pragma once
#include "Object.h"

class NPC : public df::Object {
private:
	df::Vector roomPos;
	df::Vector mapPos;
	int initPatience;
	int patience;
	int roamCooldown;
	int stateCooldown;
	std::string state;
	int roamX;
	int roamY;
	int target;
	df::Color color;
	bool loaded;
	bool isMurd;
	bool isHunting;
	bool isHuntPlayer;
	int seen;
	int murdReaction;
	int murdWait;
	int murdTimer;
	bool alive;
	
	bool faceRight;
	bool moving;

public:
	NPC(df::Color npc_color = df::WHITE, df::Vector pos = df::Vector(0, 0));

	int eventHandler(const df::Event* p_e) override;
	void step();

	// Getters and Setters
	void setColor(df::Color npc_color);
	void updateSprite();
	std::string getColorString() const;
	df::Color getColor() const;
	void setRoomPos(df::Vector new_room);
	df::Vector getRoomPos() const;
	void setMapPos(df::Vector new_mpos);
	void die();
	void setMurd(bool murd = true);
	bool getMurd() const;
	void setHunt(bool hunt = true, bool huntplayer = false);
	bool getHunt() const;
	bool getAlive() const;
	bool inLoadedRoom() const;
	int countNPCsInRoom() const;
	bool beingChased() const;

	void loadNPC();
	void unloadNPC();

	// NPC Behavior
	void checkHunt() ;					// Check if murderer should hunt
	virtual void roam();				// Move randomly in existing room
	virtual void stall();				// Wait off-screen, occasionally change rooms
	virtual void assassinate();			// Kill off-screen NPC
	virtual void leave(int speed = 15, bool nearest = false);	
										// Move to an exit. Speed is # of frames between moves. If nearest = true, move to nearest exit.
	virtual void chaseNPC();			// Move towards nearest NPC other than self
	virtual void chasePlayer();			// Move towards the player


	int draw() override;
	df::Box getBox() const override;
};