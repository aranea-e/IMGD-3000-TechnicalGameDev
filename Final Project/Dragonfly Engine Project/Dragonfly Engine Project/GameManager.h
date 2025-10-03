#pragma once

#include "Manager.h"

#define GM df::GameManager::getInstance()

namespace df {
	const std::string CONFIG_FILENAME = "df-config.txt";

	const int FRAME_TIME_DEFAULT = 33;

	class GameManager : public Manager {
	private:
		GameManager();						// Private (singleton)
		GameManager(GameManager const&);	// Don't allow copy
		void operator=(GameManager const&);	// Don't allow assignment

		bool m_game_over;	// Ends the game loop if true
		int m_step_count;	// Count of the current iteration

	public:
		~GameManager();
		static GameManager& getInstance(); // Get only instance

		int startUp();		// Start all GameManager services
		void shutDown();	// Stop GameManager services

		bool isValid(std::string event_name) const; // Returns false for non-step events

		void run();		// Runs the game loop

		void setGameOver(bool new_game_over=true); // Stops the game loop if set to true
		bool getGameOver() const;	// Returns game over status

		int getFrameTime() const;	// Returns target frame time in ms
		int getStepCount() const;	// Returns current iteration count
	};
}