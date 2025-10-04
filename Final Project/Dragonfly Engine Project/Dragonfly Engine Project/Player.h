#pragma once
#include "Object.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "EventRoomLoaded.h"

class Player : public df::Object {
private:
	int dx;
	int dy;
	int move_slowdown;
	int move_countdown;
	void step();
	void move(int dx, int dy);
	void kbd(const df::EventKeyboard* p_keyboard_event);
	/*void mouse(const df::EventMouse* p_mouse_event);*/
	void loaded(const EventRoomLoaded* p_load_event);

public:
	Player();
	int eventHandler(const df::Event* p_e) override;
};