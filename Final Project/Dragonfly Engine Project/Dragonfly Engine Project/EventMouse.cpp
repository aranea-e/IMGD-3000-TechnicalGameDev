#include "EventMouse.h"

df::EventMouse::EventMouse()
{
	setType(MSE_EVENT);
	m_mouse_action = UNDEFINED_MOUSE_ACTION;
	m_mouse_button = Mouse::UNDEFINED_MOUSE_BUTTON;
	m_mouse_xy = Vector();
}

void df::EventMouse::setMouseAction(EventMouseAction new_mouse_action)
{
	m_mouse_action = new_mouse_action;
}

df::EventMouseAction df::EventMouse::getMouseAction() const
{
	return m_mouse_action;
}

void df::EventMouse::setMouseButton(Mouse::Button new_mouse_button)
{
	m_mouse_button = new_mouse_button;
}

void df::EventMouse::setMouseButton(sf::Mouse::Button new_mouse_button) {
	switch (new_mouse_button) {
	case sf::Mouse::Button::Right:
			m_mouse_button = Mouse::RIGHT;
			break;
	case sf::Mouse::Button::Left:
		m_mouse_button = Mouse::LEFT;
		break;
	case sf::Mouse::Button::Middle:
		m_mouse_button = Mouse::MIDDLE;
		break;
	default:
		m_mouse_button = Mouse::UNDEFINED_MOUSE_BUTTON;
		break;
	}
}

df::Mouse::Button df::EventMouse::getMouseButton() const
{
	return m_mouse_button;
}

void df::EventMouse::setMousePosition(Vector new_mouse_xy)
{
	m_mouse_xy = new_mouse_xy;
}

df::Vector df::EventMouse::getMousePosition() const
{
	return m_mouse_xy;
}
