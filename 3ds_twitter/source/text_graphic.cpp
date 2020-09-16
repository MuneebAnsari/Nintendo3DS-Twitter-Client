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
#include "text_graphic.h"

TextGraphic::TextGraphic(){};

TextGraphic::TextGraphic(std::string content,
                         int contentSize,
                         u32 flags,
                         float x,
                         float y,
                         float z,
                         float scaleX,
                         float scaleY)
{

    this->content = content;
    this->contentSize = contentSize;
    this->flags = flags;
    this->x = x;
    this->y = y;
    this->z = z;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
}

void TextGraphic::getDimensions(float *width, float *height)
{
    C2D_Text graphicText;
    C2D_TextBuf graphicTextBuf = C2D_TextBufNew(this->contentSize);
    C2D_TextParse(&graphicText, graphicTextBuf, this->content.c_str());
    C2D_TextGetDimensions(&graphicText, 1.0f, 1.0f, width, height);
}

C2D_Text TextGraphic::getC2DText()
{
    C2D_Text graphicText;
    C2D_TextBuf graphicTextBuf = C2D_TextBufNew(this->contentSize);
    C2D_TextParse(&graphicText, graphicTextBuf, this->content.c_str());
    return graphicText;
}

C2D_Text TextGraphic::draw()
{
    C2D_Text graphicText;
    C2D_TextBuf graphicTextBuf = C2D_TextBufNew(this->contentSize);
    C2D_TextParse(&graphicText, graphicTextBuf, this->content.c_str());
    C2D_TextOptimize(&graphicText);
    C2D_TextBufClear(graphicTextBuf);

    C2D_DrawText(&graphicText,
                 this->flags,
                 this->x,
                 this->y,
                 this->z,
                 this->scaleX,
                 this->scaleY);

    return graphicText;
}

C2D_Text TextGraphic::draw(float wordWrap)
{
    C2D_Text graphicText;
    C2D_TextBuf graphicTextBuf = C2D_TextBufNew(this->contentSize);
    C2D_TextParse(&graphicText, graphicTextBuf, this->content.c_str());
    C2D_TextOptimize(&graphicText);
    C2D_TextBufClear(graphicTextBuf);

    C2D_DrawText(&graphicText,
                 this->flags,
                 this->x,
                 this->y,
                 this->z,
                 this->scaleX,
                 this->scaleY,
                 wordWrap);

    return graphicText;
}
