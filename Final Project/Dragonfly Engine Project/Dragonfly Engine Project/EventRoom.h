#pragma once

#include "Event.h"
#include "Vector.h"

const std::string ROOM_EVENT = "room";

class EventRoom : public df::Event {
private:
	df::Vector m_pos;	// Position Vector
public:
	EventRoom();				// Default constructor
	EventRoom(df::Vector pos);	// Position constructor

	void setPos(df::Vector new_pos);	// Position setter
	void addPos(df::Vector new_pos);	// Adds position vectors
	df::Vector getPos() const;	// Position getter
};