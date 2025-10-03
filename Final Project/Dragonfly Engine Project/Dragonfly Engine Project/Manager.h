#pragma once

// System includes
#include <string>

// Engine includes
#include "Event.h"

namespace df {
	class Manager {

	private:
		std::string m_type;		// Type identifier
		bool m_is_started;		// True if started

	protected:
		void setType(std::string type);		// Sets Type identifier

	public:
		Manager();
		virtual ~Manager();

		std::string getType() const;		// Type identifier getter
		
		// Starts Manager, returning 0 if it works and 
		// a negative number otherwise
		virtual int startUp();			

		// Shuts down Manager
		virtual void shutDown();

		// Return true if manager has been started properly
		bool isStarted() const;

		int onEvent(const df::Event* p_event) const;
	};
}