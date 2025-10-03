#pragma once

#include <string>

#include "Event.h"

namespace df {

const std::string STEP_EVENT = "df::step";

	class EventStep : public Event {
	private:
		int m_step_count; // Iteration number of game loop

	public: 
		EventStep(); // Default constructor
		EventStep(int init_step_count); // Constructor with step count

		// Getter and Setter
		void setStepCount(int new_step_count);
		int getStepCount() const;
	};
}