#pragma once

#include "Event.h"
#include "Object.h"

namespace df {
	const std::string COLLISION_EVENT = "df::collision";

	class EventCollision : public Event {
	private:
		Vector m_pos;		// Where collision occured
		Object* m_p_obj1;	// Object moving, causing collision.
		Object* m_p_obj2;	// Object being collided with.

	public:
		EventCollision();	// Create collision event at (0,0) with NULL objects
		EventCollision(Object* p_o1, Object* p_o2, Vector p);	// Create collision event between o1 and o2 at position p

		void setObject1(Object* p_new_o1);
		Object* getObject1() const;
		void setObject2(Object* p_new_o2);
		Object* getObject2() const;
		void setPosition(Vector new_pos);
		Vector getPosition() const;
	};
}