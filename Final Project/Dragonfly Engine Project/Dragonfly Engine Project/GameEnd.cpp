#include "GameEnd.h"
#include "ResourceManager.h"
#include "WorldManager.h"
#include "GameStart.h"
#include "LogManager.h"

GameEnd::GameEnd(int type)
{
	m_type = type;
	end();
}

void GameEnd::end() {
	df::ObjectList object_list = WM.getAllObjects();
	for (int i = 0; i < object_list.getCount(); i++) {
		df::Object* p_o = object_list[i];
		WM.markForDelete(p_o);
	}

	switch (m_type) {
	case 0:
		RM.getSound("Sound1")->play();
		LM.writeLog("Game End: Player Won\n");
		break;
	case 1:
		RM.getSound("Sound2")->play();
		LM.writeLog("Game End: Player Killed\n");
		break;
	case 2:
		RM.getSound("Sound3")->play();
		LM.writeLog("Game End: Player Shot Innocent\n");
		break;
	case 3:
		LM.writeLog("Game End: Player Quit\n");
		break;
	}

	new GameStart;
}