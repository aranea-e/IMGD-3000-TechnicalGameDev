#pragma once

#include "Object.h"
#include "EventCollision.h"

class Bullet : public df::Object {
private:
	void collision(const df::EventCollision* collision);
public:
	Bullet(df::Vector position, df::Vector direction, int speed = 2);	// Constructor

	int eventHandler(const df::Event* p_e) override;
};