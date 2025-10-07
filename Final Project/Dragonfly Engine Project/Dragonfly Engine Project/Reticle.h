#pragma once

// Engine Includes
#include "Object.h"

#define RETICLE_CHAR '+'

class Reticle : public df::Object {
private:
    bool searching;
    int searchFrames;
public:
    Reticle();
    int draw(void) override;
    int eventHandler(const df::Event* p_e) override;
    bool getSearch() const;
};