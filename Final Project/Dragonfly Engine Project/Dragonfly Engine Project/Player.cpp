#include "Player.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "LogManager.h"

Player::Player() {
    // set sprite
    setSprite("PC");
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
    // if a mouse event occurs, call mouse
    /*if (p_e->getType() == df::MSE_EVENT) {
        const df::EventMouse* p_mouse_event =
            dynamic_cast <const df::EventMouse*> (p_e);
        mouse(p_mouse_event);
        return 1;
    }*/
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
    // TODO: Create bounds for the player movement
    // 
    //if ((new_pos.getY() > 3) && // limits how low the ship can fly
    //    (new_pos.getY() < DM.getVertical() - 1) && // limits how high the ship can fly
    //    (new_pos.getX() > 3) && // limits how left the ship can fly
    //    (new_pos.getX() < DM.getHorizontal() / 3)) // limits how right the ship can fly
    WM.moveObject(this, new_pos);
}

// do action based on key pressed
void Player::kbd(const df::EventKeyboard* p_keyboard_event) {
    switch (p_keyboard_event->getKey()) {
        // if Q is pressed, quit out of the game (destroy hero object)
    case df::Keyboard::Q:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            WM.markForDelete(this);
        break;
        // if W pressed, move hero up
    case df::Keyboard::W:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            dy -= 1;
        if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            dy += 1;
        break;
        // if S pressed, move hero down
    case df::Keyboard::S:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            dy += 1;
        if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            dy -= 1;
        break;
        // if A pressed, move hero left
    case df::Keyboard::A:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            dx -= 1;
        if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            dx += 1;
        break;
        // if D pressed, move hero right
    case df::Keyboard::D:
        if (p_keyboard_event->getKeyboardAction() == df::KEY_PRESSED)
            dx += 1;
        if (p_keyboard_event->getKeyboardAction() == df::KEY_RELEASED)
            dx -= 1;
        break;
        // if key is not listed, just return (not necessary since it returns at the end anyhow, but good practice)
    default:
        return;
    };
    return;
}

// in charge of getting where bullets should be fired
//void Player::mouse(const df::EventMouse* p_mouse_event) {
//    // if left button pressed, fire bullet at mouse location (if cooldown allows)
//    if ((p_mouse_event->getMouseAction() == df::CLICKED) &&
//        (p_mouse_event->getMouseButton() == df::Mouse::LEFT))
//        /*fire(p_mouse_event->getMousePosition());*/
//        LM.writeLog("TODO");
//}