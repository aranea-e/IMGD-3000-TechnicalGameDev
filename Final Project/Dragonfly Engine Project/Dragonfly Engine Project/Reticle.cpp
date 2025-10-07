#include "EventMouse.h"
#include "EventStep.h"
#include "DisplayManager.h"
#include "WorldManager.h"

#include "Reticle.h"
#include "EventSearch.h"

Reticle::Reticle() {
    setType("Reticle");
    setSolidness(df::SPECTRAL);
    setAltitude(df::MAX_ALTITUDE);

    int world_horiz = (int)DM.getHorizontal();
    int world_vert = (int)DM.getVertical();
    df::Vector p(world_horiz / 2, world_vert / 2);
    setPosition(p);
}

int Reticle::eventHandler(const df::Event* p_e) {

    if (p_e->getType() == df::MSE_EVENT) {
        const df::EventMouse* p_mouse_event =
            dynamic_cast <const df::EventMouse*> (p_e);
        if (p_mouse_event->getMouseAction() == df::MOVED) {
            // Change location to new mouse position.
            setPosition(p_mouse_event->getMousePosition());
            return 1;
        }
        if (p_mouse_event->getMouseAction() == df::CLICKED) {
            if (p_mouse_event->getMouseButton() == df::Mouse::RIGHT)
            {
                if (!searching)
                {
                    setSprite("Search_Cursor");
                    searching = true;
                    searchFrames = 0;
                }
                else {
                    searching = false;
                }
            }
            
            if (p_mouse_event->getMouseButton() == df::Mouse::LEFT)
            {
                searching = false;
            }
        }
    }
    if (p_e->getType() == df::STEP_EVENT)
    {
        if (searching)
        {
            searchFrames++;
            if (searchFrames >= 150) {
                searching = false;
                EventSearch* e_s = new EventSearch();
                WM.onEvent(e_s);
            }
        }
    }

    // If get here, have ignored this event.
    return 0;
}

bool Reticle::getSearch() const
{
    return searching;
}

// Draw reticle on window.
int Reticle::draw() {
    if (searching) {
        return Object::draw();
    }
    else {
        return DM.drawCh(getPosition(), RETICLE_CHAR, df::RED);
    }
}