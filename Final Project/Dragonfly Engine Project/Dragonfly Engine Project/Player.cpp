#include "Player.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "LogManager.h"
#include "EventRoom.h"
#include "EventRoomLoaded.h"
#include "GameEnd.h"
#include "Bullet.h"

Player::Player() {
    // set sprite
    setSprite("PC_right");
    // set type
    setType("Player");
    // set position
    df::Vector p(DM.getHorizontal() / 2, DM.getVertical() / 2);
    setPosition(p);

    // set attributes for position change
    dx = 0;
    dy = 0;
    // set attributes for the cooldown on moving
    move_slowdown = 2;
    move_countdown = move_slowdown;
}

// Event Handler for Hero accounting for step, keyboard, and mouse events
int Player::eventHandler(const df::Event* p_e) {
    // if a step event occurs, call step
    if (p_e->getType() == df::STEP_EVENT) {
        step();
        return 1;
    }
    // if a keyboard event occurs, call kbd
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        const df::EventKeyboard* p_keyboard_event =
            dynamic_cast <const df::EventKeyboard*> (p_e);
        kbd(p_keyboard_event);
        return 1;
    }
    if (p_e->getType() == ROOM_LOADED_EVENT) {
        const EventRoomLoaded* p_load_event =
            dynamic_cast <const EventRoomLoaded*> (p_e);
        loaded(p_load_event);
        return 1;
    }
     //if a mouse event occurs, call mouse
    if (p_e->getType() == df::MSE_EVENT) {
        const df::EventMouse* p_mouse_event =
            dynamic_cast <const df::EventMouse*> (p_e);
        mouse(p_mouse_event);
        return 1;
    }
    return 0;
}

// step event for Hero to update private attributes
void Player::step() {
    // if dx or dy is not zero, call move to update hero position
    if (dx || dy) move(dx, dy);
    // decrease hero's move cooldown every step
    move_countdown--;
    if (move_countdown < 0)
        move_countdown = 0;
}

// updates the hero's position based on input given
void Player::move(int dx, int dy) {
    // see if the move cooldown allows for movement (return if not)
    if (move_countdown > 0)
        return;
    move_countdown = move_slowdown;

    // Update hero's position to new_pos (if new_pos is valid)
    df::Vector new_pos(getPosition().getX() + dx, getPosition().getY() + dy);

    EventRoom* p_r = nullptr;
    
    if (new_pos.getY() < 5 || new_pos.getY() > DM.getVertical() - 5)        // Vertical Bounds
    {
        new_pos.setY(getPosition().getY());
        if (new_pos.getX() > 38 && new_pos.getX() < DM.getHorizontal() - 38)
        {
            if (dy > 0)
            {
                p_r = new EventRoom(df::Vector(0, 1));
            } else {
                p_r = new EventRoom(df::Vector(0, -1));
            }
        }
    }

    if (new_pos.getX() < 21 || new_pos.getX() > DM.getHorizontal() - 21)    // Horizontal Bounds
    {
        new_pos.setX(getPosition().getX());
        if (new_pos.getY() > 10 && new_pos.getY() < DM.getVertical() - 10)
        {
            if (dx > 0)
            {
                p_r = new EventRoom(df::Vector(1, 0));
            }
            else {
                p_r = new EventRoom(df::Vector(-1, 0));
            }
        }
    }

    WM.moveObject(this, new_pos);
    if (p_r != nullptr)
    {
        WM.onEvent(p_r);
    }
}

// do action based on key pressed
void Player::kbd(const df::EventKeyboard* p_keyboard_event) {
    switch (p_keyboard_event->getKey()) {
        // if Q is pressed, quit out of the game (destroy hero object)
    case df::Keyboard::Q:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            new GameEnd(3);
        break;
        // if W pressed, move hero up
    case df::Keyboard::W:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
        {
            dy -= 1;
        }
        if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            dy += 1;
        break;
        // if S pressed, move hero down
    case df::Keyboard::S:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
        {
            dy += 1;
        }
        if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            dy -= 1;
        break;
        // if A pressed, move hero left
    case df::Keyboard::A:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
        {
            dx -= 1;
        }
        if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            dx += 1;
        break;
        // if D pressed, move hero right
    case df::Keyboard::D:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
        {
            dx += 1;
        }
        if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            dx -= 1;
        break;
        // if key is not listed, just return (not necessary since it returns at the end anyhow, but good practice)
    default:
        return;
    };
    return;
}

void Player::loaded(const EventRoomLoaded* p_load_event)
{
    df::Vector new_pos = df::Vector(getPosition().getX(), getPosition().getY());

    if (p_load_event->getPos().getX() > p_load_event->getOldPos().getX())
    {
        new_pos.setX(new_pos.getX() - 38);
    } else if (p_load_event->getPos().getX() < p_load_event->getOldPos().getX())
    {
        new_pos.setX(new_pos.getX() + 38);
    }

    if (p_load_event->getPos().getY() > p_load_event->getOldPos().getY())
    {
        new_pos.setY(new_pos.getY() - 14);
    }
    else if (p_load_event->getPos().getY() < p_load_event->getOldPos().getY())
    {
        new_pos.setY(new_pos.getY() + 14);
    }

    WM.moveObject(this, new_pos);
}

// in charge of getting where bullets should be fired
void Player::mouse(const df::EventMouse* p_mouse_event) {
    // if left button pressed, fire bullet at mouse location (if cooldown allows)
    if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
        (p_mouse_event->getMouseButton() == df::Mouse::LEFT))
        fire(p_mouse_event->getMousePosition());
}

void Player::fire(df::Vector pos) {
    df::Vector direction = (pos - getPosition());
    direction.normalize();
    new Bullet(getPosition(), direction);
}