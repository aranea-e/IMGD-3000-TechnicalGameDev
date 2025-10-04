#pragma once

#include "Event.h"
#include "Vector.h"

const std::string ROOM_LOADED_EVENT = "roomload";

class EventRoomLoaded : public df::Event {
private:
	df::Vector m_pos;	// Position Vector
	df::Vector old_pos;	// Last Position Vector
public:
	EventRoomLoaded();									// Default constructor
	EventRoomLoaded(df::Vector pos, df::Vector o_pos);	// Position constructor
	df::Vector getPos() const;			// Position getter
	df::Vector getOldPos() const;		// Last Position getter
};