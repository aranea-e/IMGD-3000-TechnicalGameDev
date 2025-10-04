#include "EventRoom.h"

EventRoom::EventRoom() : EventRoom(df::Vector(0, 0)) {}

EventRoom::EventRoom(df::Vector pos)
{
	m_pos = pos;
	setType(ROOM_EVENT);
}

void EventRoom::setPos(df::Vector new_pos)
{
	m_pos = new_pos;
}

void EventRoom::addPos(df::Vector new_pos)
{
	m_pos = m_pos + new_pos;
}

df::Vector EventRoom::getPos() const
{
	return m_pos;
}
