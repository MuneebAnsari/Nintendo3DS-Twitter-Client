#ifndef TOOLBAR_GRAPHIC_H
#define TOOLBAR_GRAPHIC_H

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <sys/types.h>
#include <cstdarg>
#include <cstdio>
#include <stdlib.h>
#include "text_graphic.h"
#include "image_graphic.h"

class ToolbarGraphic
{
private:
    float xStart;
    float yStart;

public:
    ToolbarGraphic(float xStart, float yStart);
    void draw();
};

#endif