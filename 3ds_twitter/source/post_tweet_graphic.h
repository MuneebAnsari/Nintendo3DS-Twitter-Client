#ifndef POST_TWEET_GRAPHIC_H
#define POST_TWEET_GRAPHIC_H

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <sys/types.h>
#include <cstdarg>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include "text_graphic.h"

class PostTweetGraphic
{
private:
    TextGraphic post;
    char tweetBuf[281];
    float xStart;
    float yStart;

public:
    PostTweetGraphic(float xStart, float yStart);
    void updateWithText();
    void draw();
};

#endif