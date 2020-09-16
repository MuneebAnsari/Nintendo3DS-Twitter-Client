#ifndef TEXT_GRAPHIC_H
#define TEXT_GRAPHIC_H

#include <iostream>
#include <string>
#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <sys/types.h>
#include <cstdarg>
#include <cstdio>
#include <stdlib.h>

class TextGraphic
{
private:
    std::string content;
    int contentSize;
    u32 flags;
    float x;
    float y;
    float z;
    float scaleX;
    float scaleY;

public:
    TextGraphic();
    TextGraphic(std::string content,
                int contentSize,
                u32 flags,
                float x,
                float y,
                float z,
                float scaleX,
                float scaleY);

    void getDimensions(float *width, float *height);

    C2D_Text getC2DText();
    C2D_Text draw();
    C2D_Text draw(float wordWrap);
};

#endif