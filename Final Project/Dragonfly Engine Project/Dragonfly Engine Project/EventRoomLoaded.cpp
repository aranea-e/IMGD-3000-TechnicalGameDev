#include "EventRoomLoaded.h"

EventRoomLoaded::EventRoomLoaded() : EventRoomLoaded(df::Vector(0, 0), df::Vector(0, 0)) {}

EventRoomLoaded::EventRoomLoaded(df::Vector pos, df::Vector o_pos)
{
	m_pos = pos;
	old_pos = o_pos;
	setType(ROOM_LOADED_EVENT);
}
df::Vector EventRoomLoaded::getPos() const
{
	return m_pos;
}

df::Vector EventRoomLoaded::getOldPos() const
{
	return old_pos;
}
