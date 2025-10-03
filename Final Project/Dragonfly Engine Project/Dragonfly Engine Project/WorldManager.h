#pragma once

#include "Manager.h"
#include "ObjectList.h"

#define WM df::WorldManager::getInstance()

namespace df {
	const int MAX_ALTITUDE = 4;

	class WorldManager : public Manager {
	private:
		WorldManager();							// Private (singleton)
		WorldManager(WorldManager const&);		// Don't allow copy
		void operator=(WorldManager const&);	// Don't allow assignment

		ObjectList m_updates;	// All Objects in world to update
		ObjectList m_deletions;	// All Objects in world to delete
	public:
		~WorldManager();
		static WorldManager& getInstance(); // Get only instance 

		int startUp();		// Initialize everything to empty, return 0
		void shutDown();	// Delete all game world objcets

		int insertObject(Object* p_o);	// Inserts Object to world. Returns 0 if ok, else -1
		int removeObject(Object* p_o);	// Removes Object from world. Returns 0 if ok, else -1

		ObjectList getAllObjects() const; // Return list of all Objects in world
		ObjectList objectsOfType(std::string type) const; // Return list of all Objects matching type

		void update();	// Update world, deleting objects marked for deletion

		int markForDelete(Object *p_o);	// Indicate object is to be deleted at the end of the current game loop
										// Return 0 if ok, else -1

		void draw();	// Draws all objects in world

		ObjectList getCollisions(const Object* p_o, Vector where);	// Returns list of objects collided with at position 'where'
		int moveObject(Object* p_o, Vector where);					// If collision, send events, return -1. If no collision, move object, return 0.
		bool positionsIntersect(Vector p1, Vector p2);				// Return true if two positions intersect, else false
		bool boxIntersectsBox(Box A, Box B);						// Return true if two boxes intersect, else false
		Box getWorldBox(const Object* p_o);							// Converts relative bounding box for Object to absolute world Box
		Box getWorldBox(const Object* p_o, Vector where);
	};
}