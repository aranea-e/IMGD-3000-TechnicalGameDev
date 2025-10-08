#pragma once

#include "Object.h"

class Clue : public df::Object {
private:
	df::Vector* positions;
	bool* revealed;
public:
	Clue();
	int eventHandler(const df::Event* p_e) override;
	bool isRoomTaken(df::Vector room) const;
	int inLoadedRoom() const;	// Returns index of clue in loaded room, -1 if nonedf
	int draw() override;
	df::Color getMurdColor() const;
	void search();
	int cluesFound() const;
};