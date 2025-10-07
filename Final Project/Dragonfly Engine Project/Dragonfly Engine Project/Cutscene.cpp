#include "Cutscene.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "GameEnd.h"
#include "DisplayManager.h"
#include "ResourceManager.h"

void Cutscene::deleteOthers()
{
	df::ObjectList object_list = WM.getAllObjects();
	for (int i = 0; i < object_list.getCount(); i++) {
		df::Object* p_o = object_list[i];
		if (p_o->getType() != "Cutscene")
		{
			WM.markForDelete(p_o);
		}
	}
}

Cutscene::Cutscene(int t, df::Color c)
{
	count = 0;
	type = t;
	setType("Cutscene");
	setColor(c);
	deleteOthers();
	setPosition(df::Vector(DM.getHorizontal() / 2, DM.getVertical() / 2));
}

int Cutscene::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		count++;
		if (count >= 35)
		{
			new GameEnd(type);
		}
	}
	return 0;
}

void Cutscene::setColor(df::Color c) {
	df::Sprite* spr;
	switch (type) {
	case 1:	// Killed
		spr = RM.getSprite("Death_Cutscene");
		break;
	case 2:	// Shot Inno
		spr = RM.getSprite("Inno_Cutscene");
		break;
	case 0:	// Won
	default:
		spr = RM.getSprite("Win_Cutscene");
		break;
	}
	spr->setColor(c);
	setSprite(spr->getLabel());
}