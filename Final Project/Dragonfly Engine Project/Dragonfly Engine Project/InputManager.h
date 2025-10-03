#pragma once

// System includes


// Engine includes
#include "Manager.h"

#define IM df::InputManager::getInstance()

namespace df {
	class InputManager : public Manager {
	private:
		InputManager();							// Private (singleton)
		InputManager(InputManager const&);		// Don't allow copy
		void operator=(InputManager const&);	// Don't allow assignment


	public:
		static InputManager& getInstance(); // Get only instance 

		int startUp();		// Start up the InputManager. Ready window to capture input. Return 0 if ok, else return -1
		void shutDown();	// Shut down the InputManager. Revert back to normal window mode.

		void getInput() const; // Get input from keyboard and mouse. Pass event to all Objects.
	};
}
