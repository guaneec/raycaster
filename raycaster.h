#pragma once

#include "defs.h"

class RayCaster
{
public:
    virtual void Start(uint16_t playerX, uint16_t playerY, int16_t playerA) = 0;

    virtual void Trace(uint16_t screenX,
                       uint8_t *screenY,
                       uint8_t *textureNo,
                       uint8_t *textureX,
                       uint16_t *textureY,
                       uint16_t *textureStep) = 0;

    RayCaster(){};

    ~RayCaster(){};
};
