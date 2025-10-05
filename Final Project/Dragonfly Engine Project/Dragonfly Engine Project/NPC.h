#pragma once
#include "Object.h"

class NPC : public df::Object {
private:
	df::Vector roomPos;
	df::Vector mapPos;
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

public:
	NPC();
	NPC(df::Color npc_color);
	void setColor(df::Color npc_color);
	std::string getColorString() const;
	void setRoomPos(df::Vector new_room);
	df::Vector getRoomPos() const;
	void setMurd(bool murd = true);
	bool getMurd() const;
	void setHunt(bool hunt = true);
	bool getHunt() const;
	virtual void roam();
	bool inLoadedRoom();
	void loadNPC();
	void unloadNPC();
	int eventHandler(const df::Event* p_e) override;
	void step();
	virtual void stall();
	virtual void leave();
};