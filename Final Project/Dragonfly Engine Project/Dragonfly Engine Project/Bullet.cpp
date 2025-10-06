#include "Bullet.h"
#include "EventCollision.h"
#include "EventOut.h"
#include "NPC.h"
#include "GameEnd.h"
#include "WorldManager.h"

Bullet::Bullet(df::Vector position, df::Vector direction, int speed)
{
	setPosition(position);
	setDirection(direction);
	setSpeed(speed);
	setType("bullet");
	setSprite("Bullet");
	setSolidness(df::SOFT);
	setAltitude(3);
}

int Bullet::eventHandler(const df::Event* p_e)
{
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event =
			dynamic_cast <const df::EventCollision*> (p_e);
		collision(p_collision_event);
		return 1;
	}
	if (p_e->getType() == df::OUT_EVENT)
	{
		WM.markForDelete(this);
	}
	return 0;
}

void Bullet::collision(const df::EventCollision* collision)
{
	NPC* c_npc = nullptr;
	if (collision->getObject1()->getType() == "NPC")
	{
		c_npc = (NPC*)collision->getObject1();
	} 
	if (collision->getObject2()->getType() == "NPC")
	{
		c_npc = (NPC*)collision->getObject2();
	}

	if (c_npc != nullptr && c_npc->getAlive() && WM.objectsOfType("GameEnd").getCount() == 0) {
		if (c_npc->getMurd())
		{
			new GameEnd(0);
		}
		else {
			new GameEnd(2);
		}
	}
}