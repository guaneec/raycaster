#pragma once

#include "game.h"
#include "raycaster.h"

class Renderer
{
    RayCaster *_rc;

    inline static uint32_t GetARGB(uint8_t brightness)
    {
        return (brightness << 16) + (brightness << 8) + brightness;
    }

public:
    void TraceFrame(Game *g, uint32_t *frameBuffer);
    Renderer(RayCaster *rc, bool color = false) : color(color) { _rc = rc; };
    ~Renderer(){};

private:
    bool color;
};
