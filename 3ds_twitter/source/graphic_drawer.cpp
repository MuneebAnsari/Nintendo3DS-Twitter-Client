
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
#include "graphic_drawer.h"

GraphicDrawer::GraphicDrawer() {}

void GraphicDrawer::drawTweets(Tweet *head, float *screenSpace, float *xStart, float *yStart)
{
    while (head != NULL)
    {
        TweetGraphic currTweetGraphic = TweetGraphic(head->text, *xStart, *yStart);

        if (*screenSpace > 0)
        {
            currTweetGraphic.draw();
            *yStart = *yStart + currTweetGraphic.getHeight() + 10;
            *screenSpace -= *yStart;
            head = head->next;
        }
        else
        {
            break;
        }
    }
}