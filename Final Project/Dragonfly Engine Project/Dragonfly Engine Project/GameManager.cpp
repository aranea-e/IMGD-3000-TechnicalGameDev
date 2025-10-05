#include <Windows.h>

#include "GameManager.h"
#include "Clock.h"
#include "LogManager.h"
#include "EventStep.h"
#include "ObjectList.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "InputManager.h"
#include "Frame.h"

df::GameManager::GameManager() {	// Private, only called by getInstance()
	setGameOver(false);
	m_step_count = 0;
	startUp();
}

df::GameManager::~GameManager()
{
	shutDown();
}

int df::GameManager::startUp() {
	LM.startUp();
	LM.setFlush(true);
	WM.startUp();
	DM.startUp();
	IM.startUp();
	timeBeginPeriod(1);
	return 0;
}

void df::GameManager::shutDown() {
	LM.shutDown();
	WM.shutDown();
	DM.shutDown();
	timeEndPeriod(1);
}

df::GameManager& df::GameManager::getInstance()
{
	static GameManager gm;	// Static variable persists after running
	return gm;
}

bool df::GameManager::isValid(std::string event_name) const
{
	return event_name == "step";
}

void df::GameManager::run() // Game loop
{
	df::Clock clock;
	while (!m_game_over) {
		m_step_count++;
		clock.delta();

		// Get Input
		IM.getInput();

		// Update game world state
		EventStep s(m_step_count);
		onEvent(&s);

		WM.update();

		// Draw current scene to back buffer
		WM.draw();
		// Swap back buffer to current buffer
		DM.swapBuffers();
		

		// Sleep until next step
		int elapsed = (int)(clock.delta() / 1000);
		int sleep_time = getFrameTime() - elapsed;
		if (sleep_time > 0) {
			Sleep(sleep_time);
		}
		else {
			//LM.writeLog("!!sleep_time was <= 0, not sleeping. Game Lag.!!\n");
		}
	}
}

void df::GameManager::setGameOver(bool new_game_over)
{
	m_game_over = new_game_over;
}

bool df::GameManager::getGameOver() const
{
	return m_game_over;
}

int df::GameManager::getFrameTime() const
{
	return FRAME_TIME_DEFAULT;
}

int df::GameManager::getStepCount() const
{
	return 0;
}
