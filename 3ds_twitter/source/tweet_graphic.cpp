#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <sys/types.h>
#include <cstdarg>
#include <cstdio>
#include <stdlib.h>
#include "tweet_graphic.h"

const u32 TweetGraphic::bgClr = C2D_Color32(0xE3, 0xF1, 0xFC, 0xFF);

TweetGraphic::TweetGraphic(const char *rawText, float xStart, float yStart)
{
    this->rawText = rawText;
    this->xStart = xStart;
    this->yStart = yStart;
}

float TweetGraphic::getHeight()
{
    return this->height;
}

float TweetGraphic::getWidth()
{
    return this->width;
}

const char *TweetGraphic::getRawText()
{
    return this->rawText;
}

void TweetGraphic::draw()
{
    // Initialize text graphic
    C2D_Text graphicText;
    C2D_TextBuf graphicTextBuf = C2D_TextBufNew(300);
    C2D_TextParse(&graphicText, graphicTextBuf, this->rawText);
    C2D_TextOptimize(&graphicText);
    C2D_TextBufClear(graphicTextBuf);

    // Set tweet height and width to fit tweet content
    C2D_TextGetDimensions(&graphicText, 1.0f, 1.0f, &this->width, &this->height);
    this->height = (this->height * (graphicText.width / 1569)) + 20;
    this->width = GSP_SCREEN_HEIGHT_TOP - 40;

    // Draw tweet container
    C2D_DrawRectSolid(this->xStart,
                      this->yStart,
                      0,
                      this->width,
                      this->height,
                      this->bgClr);

    // Draw text within tweet container and word wrap text
    // within bounding tweet container with a padding of 5.
    C2D_DrawText(&graphicText,
                 C2D_AlignLeft | C2D_WordWrap,
                 this->xStart + 5,
                 this->yStart + 5,
                 0,
                 0.5f,
                 0.5f,
                 this->width - 5);
}
