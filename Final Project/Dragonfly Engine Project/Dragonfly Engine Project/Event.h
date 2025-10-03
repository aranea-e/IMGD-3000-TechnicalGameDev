#pragma once

#include <string>

namespace df {

const std::string UNDEFINED_EVENT = "df::undefined";

	class Event {
	private:
		std::string event_type;

	public:
		Event();
		virtual ~Event();

		// Getter and Setter
		void setType(std::string new_type);
		std::string getType() const;
	};
}