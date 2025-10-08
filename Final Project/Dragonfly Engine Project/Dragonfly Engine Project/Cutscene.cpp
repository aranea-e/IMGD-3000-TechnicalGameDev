#include "Cutscene.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "GameEnd.h"
#include "DisplayManager.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "NPC.h"
#include "Clue.h"

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
	getScore();

	if (WM.objectsOfType("Cutscene").getCount() > 1)
	{
		LM.writeLog("!!Multiple Cutscenes!!\n");
		WM.markForDelete(this);
		return;
	}
	setSolidness(df::SPECTRAL);

	count = 0;
	type = t;
	setType("Cutscene");
	setColor(c);
	deleteOthers();
	setPosition(df::Vector(DM.getHorizontal() / 2, DM.getVertical() / 2));
	LM.writeLog("Cutscene: %d\n", t);
}

int Cutscene::getEndType()
{
	return type;
}

void Cutscene::getScore()
{
	npcs = 0;
	df::ObjectList objs = WM.objectsOfType("NPC");
	for (int i = 0; i < objs.getCount(); i++)
	{
		NPC* npc = (NPC*)objs[i];
		if (npc->getAlive() && !npc->getMurd())
		{
			npcs += 1;
		}
	}

	Clue* cluesObj = (Clue*)WM.objectsOfType("Clue")[0];
	clues = cluesObj->cluesFound();
}

int Cutscene::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		count++;
		if (count >= 35)
		{
			new GameEnd(type, npcs, clues);
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

int Cutscene::draw()
{
	if (getAnimation().getSlowdownCount() == 0 && getAnimation().getIndex() == 2 && type != 1)
	{
		RM.getSound("NPC_Shot")->play();
	}
	return Object::draw();
}
