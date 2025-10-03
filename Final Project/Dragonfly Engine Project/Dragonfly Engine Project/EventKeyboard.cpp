#include "EventKeyboard.h"

df::EventKeyboard::EventKeyboard()
{
	setType(KEYBOARD_EVENT);
	m_key_val = Keyboard::UNDEFINED_KEY;
	m_keyboard_action = UNDEFINED_KEYBOARD_ACTION;
}

void df::EventKeyboard::setKey(Keyboard::Key new_key)
{
	m_key_val = new_key;
}

void df::EventKeyboard::setKey(sf::Keyboard::Key new_key) {
	switch (new_key) {
	case sf::Keyboard::Key::Space:
		m_key_val = Keyboard::SPACE;
		break;
	case sf::Keyboard::Key::Enter:
		m_key_val = Keyboard::RETURN;
		break;
	case sf::Keyboard::Key::Escape:
		m_key_val = Keyboard::ESCAPE;
		break;
	case sf::Keyboard::Key::Tab:
		m_key_val = Keyboard::TAB;
		break;
	case sf::Keyboard::Key::Left:
		m_key_val = Keyboard::LEFTARROW;
		break;
	case sf::Keyboard::Key::Right:
		m_key_val = Keyboard::RIGHTARROW;
		break;
	case sf::Keyboard::Key::Up:
		m_key_val = Keyboard::UPARROW;
		break;
	case sf::Keyboard::Key::Down:
		m_key_val = Keyboard::DOWNARROW;
		break;
	case sf::Keyboard::Key::Pause:
		m_key_val = Keyboard::PAUSE;
		break;
	case sf::Keyboard::Key::Subtract:
		m_key_val = Keyboard::MINUS;
		break;
	case sf::Keyboard::Key::Add:
		m_key_val = Keyboard::PLUS;
		break;
	case sf::Keyboard::Key::Grave:
		m_key_val = Keyboard::TILDE;
		break;
	case sf::Keyboard::Key::Period:
		m_key_val = Keyboard::PERIOD;
		break;
	case sf::Keyboard::Key::Comma:
		m_key_val = Keyboard::COMMA;
		break;
	case sf::Keyboard::Key::Slash:
		m_key_val = Keyboard::SLASH;
		break;
	case sf::Keyboard::Key::LControl:
		m_key_val = Keyboard::LEFTCONTROL;
		break;
	case sf::Keyboard::Key::RControl:
		m_key_val = Keyboard::RIGHTCONTROL;
		break;
	case sf::Keyboard::Key::LShift:
		m_key_val = Keyboard::LEFTSHIFT;
		break;
	case sf::Keyboard::Key::RShift:
		m_key_val = Keyboard::RIGHTSHIFT;
		break;
	case sf::Keyboard::Key::F1:
		m_key_val = Keyboard::F1;
		break;
	case sf::Keyboard::Key::F2:
		m_key_val = Keyboard::F2;
		break;
	case sf::Keyboard::Key::F3:
		m_key_val = Keyboard::F3;
		break;
	case sf::Keyboard::Key::F4:
		m_key_val = Keyboard::F4;
		break;
	case sf::Keyboard::Key::F5:
		m_key_val = Keyboard::F5;
		break;
	case sf::Keyboard::Key::F6:
		m_key_val = Keyboard::F6;
		break;
	case sf::Keyboard::Key::F7:
		m_key_val = Keyboard::F7;
		break;
	case sf::Keyboard::Key::F8:
		m_key_val = Keyboard::F8;
		break;
	case sf::Keyboard::Key::F9:
		m_key_val = Keyboard::F9;
		break;
	case sf::Keyboard::Key::F10:
		m_key_val = Keyboard::F10;
		break;
	case sf::Keyboard::Key::F11:
		m_key_val = Keyboard::F11;
		break;
	case sf::Keyboard::Key::F12:
		m_key_val = Keyboard::F12;
		break;
	case sf::Keyboard::Key::A:
		m_key_val = Keyboard::A;
		break;
	case sf::Keyboard::Key::B:
		m_key_val = Keyboard::B;
		break;
	case sf::Keyboard::Key::C:
		m_key_val = Keyboard::C;
		break;
	case sf::Keyboard::Key::D:
		m_key_val = Keyboard::D;
		break;
	case sf::Keyboard::Key::E:
		m_key_val = Keyboard::E;
		break;
	case sf::Keyboard::Key::F:
		m_key_val = Keyboard::F;
		break;
	case sf::Keyboard::Key::G:
		m_key_val = Keyboard::G;
		break;
	case sf::Keyboard::Key::H:
		m_key_val = Keyboard::H;
		break;
	case sf::Keyboard::Key::I:
		m_key_val = Keyboard::I;
		break;
	case sf::Keyboard::Key::J:
		m_key_val = Keyboard::J;
		break;
	case sf::Keyboard::Key::K:
		m_key_val = Keyboard::K;
		break;
	case sf::Keyboard::Key::L:
		m_key_val = Keyboard::L;
		break;
	case sf::Keyboard::Key::M:
		m_key_val = Keyboard::M;
		break;
	case sf::Keyboard::Key::N:
		m_key_val = Keyboard::N;
		break;
	case sf::Keyboard::Key::O:
		m_key_val = Keyboard::O;
		break;
	case sf::Keyboard::Key::P:
		m_key_val = Keyboard::P;
		break;
	case sf::Keyboard::Key::Q:
		m_key_val = Keyboard::Q;
		break;
	case sf::Keyboard::Key::R:
		m_key_val = Keyboard::R;
		break;
	case sf::Keyboard::Key::S:
		m_key_val = Keyboard::S;
		break;
	case sf::Keyboard::Key::T:
		m_key_val = Keyboard::T;
		break;
	case sf::Keyboard::Key::U:
		m_key_val = Keyboard::U;
		break;
	case sf::Keyboard::Key::V:
		m_key_val = Keyboard::V;
		break;
	case sf::Keyboard::Key::W:
		m_key_val = Keyboard::W;
		break;
	case sf::Keyboard::Key::X:
		m_key_val = Keyboard::X;
		break;
	case sf::Keyboard::Key::Y:
		m_key_val = Keyboard::Y;
		break;
	case sf::Keyboard::Key::Z:
		m_key_val = Keyboard::Z;
		break;
	case sf::Keyboard::Key::Num1:
		m_key_val = Keyboard::NUM1;
		break;
	case sf::Keyboard::Key::Num2:
		m_key_val = Keyboard::NUM2;
		break;
	case sf::Keyboard::Key::Num3:
		m_key_val = Keyboard::NUM3;
		break;
	case sf::Keyboard::Key::Num4:
		m_key_val = Keyboard::NUM4;
		break;
	case sf::Keyboard::Key::Num5:
		m_key_val = Keyboard::NUM5;
		break;
	case sf::Keyboard::Key::Num6:
		m_key_val = Keyboard::NUM6;
		break;
	case sf::Keyboard::Key::Num7:
		m_key_val = Keyboard::NUM7;
		break;
	case sf::Keyboard::Key::Num8:
		m_key_val = Keyboard::NUM8;
		break;
	case sf::Keyboard::Key::Num9:
		m_key_val = Keyboard::NUM9;
		break;
	case sf::Keyboard::Key::Num0:
		m_key_val = Keyboard::NUM0;
		break;
	default:
		m_key_val = Keyboard::UNDEFINED_KEY;
		break;
	}
}

df::Keyboard::Key df::EventKeyboard::getKey() const
{
	return m_key_val;
}

void df::EventKeyboard::setKeyboardAction(EventKeyboardAction new_action)
{
	m_keyboard_action = new_action;
}

df::EventKeyboardAction df::EventKeyboard::getKeyboardAction() const
{
	return m_keyboard_action;
}
