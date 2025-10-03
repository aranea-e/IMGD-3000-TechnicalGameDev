// System includes
#include <string>

// Engine includes
#include "Manager.h"
#include "ObjectList.h"
#include "WorldManager.h"

df::Manager::Manager() {
	m_type = "";
	m_is_started = false;
}

df::Manager::~Manager() {
	shutDown();
}

std::string df::Manager::getType() const {
	return m_type;
}

void df::Manager::setType(std::string type) {
	m_type = type;
}

int df::Manager::startUp() {
	m_is_started = true;
	return 0;
}

void df::Manager::shutDown() {
	m_is_started = false;
}

bool df::Manager::isStarted() const {
	return m_is_started;
}

int df::Manager::onEvent(const df::Event* p_event) const
{
	int count = 0;
	df::ObjectList all_objects = WM.getAllObjects();
	for (int i = 0; i < all_objects.getCount(); i++)
	{
		all_objects[i]->eventHandler(p_event);
		count++;
	}
	return count;
}
