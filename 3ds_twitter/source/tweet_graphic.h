#ifndef TWEET_GRAPHIC_H
#define TWEET_GRAPHIC_H

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <sys/types.h>
#include <cstdarg>
#include <cstdio>
#include <stdlib.h>

class TweetGraphic
{
private:
    float height;
    float width;
    float xStart;
    float yStart;
    static const u32 bgClr;
    const char *rawText;

public:
    TweetGraphic(const char *rawText, float xStart, float yStart);
    float getHeight();
    float getWidth();
    const char *getRawText();

    void draw();
};

#endif