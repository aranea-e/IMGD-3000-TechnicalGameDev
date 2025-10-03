#pragma once

#include <string>

#include "Event.h"
#include "Vector.h"
#include <SFML/Window/Mouse.hpp>


namespace df {

	const std::string MSE_EVENT = "df::mouse";

	// Set of mouse actions recognized by Dragonfly.
	enum EventMouseAction {
		UNDEFINED_MOUSE_ACTION = -1,
		CLICKED,
		MOVED,
	};

	// Set of mouse buttons recognized by Dragonfly.
	namespace Mouse {
		enum Button {
			UNDEFINED_MOUSE_BUTTON = -1,
			LEFT,
			RIGHT,
			MIDDLE,
		};
	} // end of namespace Mouse

	class EventMouse : public Event {
	private:
		EventMouseAction m_mouse_action;	// Mouse action.
		Mouse::Button m_mouse_button;		// Mouse button.
		Vector m_mouse_xy;					// Mouse (x,y) coordinates.

	public:
		EventMouse(); // Default constructor

		
		void setMouseAction(EventMouseAction new_mouse_action);	// Set mouse event's action.
		EventMouseAction getMouseAction() const;				// Get mouse event's action.
		
		void setMouseButton(Mouse::Button new_mouse_button);	// Set mouse event's button.
		void setMouseButton(sf::Mouse::Button new_mouse_button);// Set button from sfml button
		Mouse::Button getMouseButton() const;					// Get mouse event's button.
		
		void setMousePosition(Vector new_mouse_xy);				// Set mouse event's position.
		Vector getMousePosition() const;						// Get mouse event's position.
	};
}