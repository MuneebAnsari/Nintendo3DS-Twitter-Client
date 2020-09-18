#ifndef TWEET_GRAPHIC_H
#define TWEET_GRAPHIC_H

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <string>
#include "image_graphic.h"
#include "text_graphic.h"
#include "models.h"

class TweetGraphic
{
private:
    Tweet *tweet;
    TextGraphic tweetTextGraphic;
    float height;
    float width;
    float xStart;
    float yStart;
    static const u32 bgClr;

    void initBounds();

public:
    TweetGraphic(Tweet *tweet, float xStart, float yStart);
    float &getHeight();
    float &getWidth();
    Tweet &getTweet();
    void draw();
};

#endif