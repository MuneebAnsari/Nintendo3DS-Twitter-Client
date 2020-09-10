#ifndef GRAPHIC_DRAWER_H
#define GRAPHIC_DRAWER_H

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <sys/types.h>
#include <cstdarg>
#include <cstdio>
#include <stdlib.h>
#include "models.h"
#include "tweet_graphic.h"

class GraphicDrawer
{

public:
    GraphicDrawer();
    void drawTweets(Tweet *head, float *screenSpace, float *xStart, float *yStart);
};

#endif