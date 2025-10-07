#pragma once

#include "Event.h"


const std::string SEARCH_EVENT = "search";

class EventSearch : public df::Event {
public:
	EventSearch();
};