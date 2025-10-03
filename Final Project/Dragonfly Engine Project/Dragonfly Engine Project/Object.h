#pragma once

// System includes
#include <string>

// Engine includes
#include "Vector.h"
#include "Event.h"
#include "Animation.h"
#include "Box.h"

namespace df {
	enum Solidness {
		HARD,		// Objcet causes collisions
		SOFT,		// Object causes collisions, but doesn't impede
		SPECTRAL,	// Object doesn't cause collisions
	};

	class Object {
	private:
		int m_id;				// Unique engine-defined identifier
		std::string m_type;		// Programmer-defined type
		Vector m_position;		// Position
		int m_altitude;			// 0 to MAX supported (lower drawn first)

		Vector m_direction;		// Direciton vector
		float m_speed;			// Object speed in direction

		Solidness m_solidness;	// Object solidness

		Animation m_animation;	// Object animation

		Box m_box;				// Bounding box

	public:
		Object();			// Constructor. Set default paramaters and add to WorldManager.
		virtual ~Object();	// Destructor. Remove from WorldManager.

		// Getters and Setters
		void setId(int new_id);
		int getId() const;
		void setType(std::string new_type);
		std::string getType() const;
		void setPosition(Vector new_pos);
		Vector getPosition() const;
		int setAltitude(int newAltitude);	// Checks for range [0, MAX_ALTITUDE]. Returns 0 if ok, else -1
		int getAltitude() const;
		void setSpeed(float speed);
		float getSpeed() const;
		void setDirection(Vector new_direction);
		Vector getDirection() const;
		void setVelocity(Vector new_velocity);
		Vector getVelocity() const;
		Vector predictPosition();
		int setSolidness(Solidness new_solidness);	// return 0 if ok, else -1
		Solidness getSolidness() const;
		bool isSolid() const;				// true for HARD or SOFT, false for SPECTRAL
		int setSprite(std::string sprite_label);	// return 0 if ok, else -1
		void setAnimation(Animation newAnimation);	
		Animation getAnimation() const;
		void setBox(Box new_box);
		Box getBox() const;

		// Handle event (default is to ignore everything
		// Return 0 if ignored, else 1 if handled
		virtual int eventHandler(const Event* p_e);

		virtual int draw();
	};
}