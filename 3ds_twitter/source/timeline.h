#ifndef TIMELINE_H
#define TIMELINE_H

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <sys/types.h>
#include <cstdarg>
#include <cstdio>
#include <stdlib.h>
#include "tweet_graphic.h"
#include "models.h"

class Timeline
{
private:
    Tweet *head;
    Tweet *last;
    C3D_RenderTarget *target;
    float xs;
    float ys;
    float screenSpace;
    int pageNum;
    int numTweetsOnPage;

    void showPreviousPage();
    void resetFrame();

public:
    Timeline(Tweet **head, C3D_RenderTarget *target);
    void scrollDown(u32 kDown);
    void scrollUp(u32 kDown);
    void draw();
};

#endif