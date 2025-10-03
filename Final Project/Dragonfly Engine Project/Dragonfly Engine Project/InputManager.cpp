#include "InputManager.h"
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "LogManager.h"

df::InputManager::InputManager() {	// Private, only called by getInstance()
	setType("InputManager");
	startUp();
}

df::InputManager& df::InputManager::getInstance()
{
	static InputManager im;	// Static variable persists after running
	return im;
}

int df::InputManager::startUp() {
	sf::RenderWindow* p_window = DM.getWindow();

	if (p_window == NULL)
	{
		return -1;
	}

	p_window->setKeyRepeatEnabled(false);

	return Manager::startUp();
}

void df::InputManager::shutDown() {
	sf::RenderWindow* p_window = DM.getWindow();
	p_window->setKeyRepeatEnabled(true);
	Manager::shutDown();
}

void df::InputManager::getInput() const
{
	sf::RenderWindow* p_window = DM.getWindow();
	if (p_window == NULL)
	{
		LM.writeLog("getInput(): No window found\n");
		return;
	}
	while (const std::optional<sf::Event> p_event = p_window->pollEvent()) {
		sf::Event e = p_event.value();

		if (p_event->is<sf::Event::KeyPressed>()) {
			sf::Event::KeyPressed* p_kb_event = reinterpret_cast<sf::Event::KeyPressed*>(&e);

			EventKeyboard event;
			event.setKey(p_kb_event->code);
			event.setKeyboardAction(KEY_PRESSED);
			onEvent(&event);
		}
		else if (p_event->is<sf::Event::KeyReleased>()) {
			sf::Event::KeyPressed* p_kb_event = reinterpret_cast<sf::Event::KeyPressed*>(&e);

			EventKeyboard event;
			event.setKey(p_kb_event->code);
			event.setKeyboardAction(KEY_RELEASED);
			onEvent(&event);
		}
		else if (p_event->is<sf::Event::MouseMoved>()) {
			sf::Event::MouseMoved* p_mse_event = reinterpret_cast<sf::Event::MouseMoved*>(&e);

			EventMouse event;
			event.setMouseAction(MOVED);
			event.setMousePosition(Vector((float)p_mse_event->position.x
				/ ((float)DM.getHorizontalPixels() / DM.getHorizontal()),
				(float)p_mse_event->position.y
				/ ((float)DM.getVerticalPixels() / DM.getVertical())));
			onEvent(&event);
		}
		else if (p_event->is<sf::Event::MouseButtonPressed>()) {
			sf::Event::MouseButtonPressed* p_mse_event = reinterpret_cast<sf::Event::MouseButtonPressed*>(&e);

			EventMouse event;
			event.setMouseAction(CLICKED);
			event.setMouseButton(p_mse_event->button);
			event.setMousePosition(Vector((float)p_mse_event->position.x
									  / ((float)DM.getHorizontalPixels() / DM.getHorizontal()),
								   (float)p_mse_event->position.y
									  / ((float)DM.getVerticalPixels() / DM.getVertical())));
			onEvent(&event);
		}
	}
}

