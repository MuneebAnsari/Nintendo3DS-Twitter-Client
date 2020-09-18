#ifndef POST_TWEET_GRAPHIC_H
#define POST_TWEET_GRAPHIC_H
#include <iostream>
#include <string>
#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include "image_graphic.h"
#include "text_graphic.h"

class PostTweetGraphic
{
private:
    TextGraphic post;
    std::string tweetBuf;
    float xStart;
    float yStart;

public:
    PostTweetGraphic(float xStart, float yStart);
    std::string updateWithText();
    void clear();
    void draw();
};

#endif