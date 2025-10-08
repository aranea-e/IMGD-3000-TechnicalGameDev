#include "WorldManager.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "EventCollision.h"
#include "EventOut.h"

df::WorldManager::WorldManager() {	// Private, only called by getInstance()
	setType("WorldManager");
	startUp();
}

df::WorldManager::~WorldManager()
{
	shutDown();
}

df::WorldManager& df::WorldManager::getInstance()
{
	static WorldManager wm;	// Static variable persists after running
	return wm;
}

int df::WorldManager::startUp() {
	return Manager::startUp();
}

void df::WorldManager::shutDown() {
	ObjectList ol = m_updates;
	for (int i = 0; i < ol.getCount(); i++) {
		removeObject(ol[i]);
	}

	Manager::shutDown();
}

int df::WorldManager::insertObject(Object* p_o)
{
	return m_updates.insert(p_o);
}

int df::WorldManager::removeObject(Object* p_o)
{
	return m_updates.remove(p_o);
}

df::ObjectList df::WorldManager::getAllObjects() const
{
	return m_updates;
}

df::ObjectList df::WorldManager::objectsOfType(std::string type) const
{
	ObjectList out;
	for (int i = 0; i < m_updates.getCount(); i++)
	{
		if (strcmp(m_updates[i]->getType().c_str(), type.c_str()) == 0)
		{
			out.insert(m_updates[i]);

		}
	}
	return out;
}

void df::WorldManager::update()
{
	for (int i = 0; i < m_deletions.getCount(); i++) {
		LM.writeLog("Deleting: %s\n", m_deletions[i]->getType().c_str());
		m_deletions[i]->~Object();
	}
	m_deletions.clear();

	for (int i = 0; i < m_updates.getCount(); i++) {
		Vector new_pos = m_updates[i]->predictPosition();
		if (new_pos != m_updates[i]->getPosition()) {
			moveObject(m_updates[i], new_pos);
		}
	}
}

int df::WorldManager::markForDelete(Object *p_o)
{
	for (int i = 0; i < m_deletions.getCount(); i++)
	{
		if (m_deletions[i] == p_o) {
			return 0;
		}
	}
	return m_deletions.insert(p_o);
}

void df::WorldManager::draw() {
	for (int alt = 0; alt <= MAX_ALTITUDE; alt++)
	{
		for (int i = 0; i < m_updates.getCount(); i++)
		{
			if (m_updates[i]->getAltitude() == alt) {
				m_updates[i]->draw();
			}
		}
	}
}

df::ObjectList df::WorldManager::getCollisions(const Object* p_o, Vector where)
{
	ObjectList collision_list;
	Box b = getWorldBox(p_o, where);

	for (int i = 0; i < m_updates.getCount(); i++) {
		Object* p_temp_o = m_updates[i];

		if (p_temp_o != p_o) {
			Box b_temp = getWorldBox(p_temp_o);
			if ((boxIntersectsBox(b, b_temp)) &&
				(p_temp_o->isSolid()))
			{
				collision_list.insert(p_temp_o);
			}
		}
	}

	return collision_list;
}

int df::WorldManager::moveObject(Object* p_o, Vector where)
{
	if (p_o->isSolid()) {
		ObjectList list = getCollisions(p_o, where);

		if (!list.isEmpty()) {
			bool do_move = true;

			for (int i = 0; i < list.getCount(); i++) {
				Object* p_temp_o = list[i];
				EventCollision c(p_o, p_temp_o, where);
				p_o->eventHandler(&c);
				p_temp_o->eventHandler(&c);

				if (p_o->getSolidness() == HARD && p_temp_o->getSolidness() == HARD) {
					do_move = false;
				}

			}

			if (do_move == false) {
				return -1;
			}
		}
	}

	p_o->setPosition(where);
	if (where.getX() < 0 || where.getY() < 0 || where.getX() > DM.getHorizontal() || where.getY() > DM.getVertical()) {
		EventOut ov;
		p_o->eventHandler(&ov);
	}
	return 0;
}

bool df::WorldManager::positionsIntersect(Vector p1, Vector p2)
{
	if ((abs(p1.getX() - p2.getX()) <= 1) && (abs(p1.getY() - p2.getY()) <= 1)) {
		return true;
	} 
	return false;
}

bool df::WorldManager::boxIntersectsBox(Box A, Box B)
{
	bool x_overlap = (B.getCorner().getX() <= A.getCorner().getX() && A.getCorner().getX() <= (B.getCorner().getX() + B.getHorizontal())) ||
		(A.getCorner().getX() <= B.getCorner().getX() && B.getCorner().getX() <= (A.getCorner().getX() + A.getHorizontal()));
	bool y_overlap = (B.getCorner().getY() <= A.getCorner().getY() && A.getCorner().getY() <= (B.getCorner().getY() + B.getHorizontal())) ||
		(A.getCorner().getY() <= B.getCorner().getY() && B.getCorner().getY() <= (A.getCorner().getY() + A.getHorizontal()));

	return x_overlap && y_overlap;
}

df::Box df::WorldManager::getWorldBox(const Object* p_o)
{
	return getWorldBox(p_o, p_o->getPosition());
}

df::Box df::WorldManager::getWorldBox(const Object* p_o, Vector where)
{
	Box box = p_o->getBox();
	Vector corner = box.getCorner();
	corner.setX(corner.getX() + where.getX());
	corner.setY(corner.getY() + where.getY());
	box.setCorner(corner); 
	return box;
}
