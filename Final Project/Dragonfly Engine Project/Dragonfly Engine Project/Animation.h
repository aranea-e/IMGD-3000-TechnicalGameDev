#pragma once

#include <string>

#include "Sprite.h"
#include "Box.h"

namespace df {
	class Animation {
	private:
		Sprite* m_p_sprite;		// Sprite associated with Animation
		std::string m_name;		// Sprite name in ResourceManager
		int m_index;			// Current index frame for sprite
		int m_slowdown_count;	// Slowdown counter

	public:
		Animation();	// Constructor

		// Getters and Setters
		void setSprite(Sprite* p_new_sprite);
		Sprite* getSprite() const;
		void setName(std::string new_name);
		std::string getName() const;
		void setIndex(int new_index);
		int getIndex() const;
		void setSlowdownCount(int new_slowdown_count);	// -1 means stop animation
		int getSlowdownCount() const;
		Box getBox() const;	// Get bounding box of sprite

		// Draw frame at (x,y)
		// Accounts for slowdown, advances Sprite frame
		// Return 0 if ok, else -1
		int draw(Vector position);
	};
}