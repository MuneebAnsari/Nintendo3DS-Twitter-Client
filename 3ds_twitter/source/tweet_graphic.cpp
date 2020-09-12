#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <sys/types.h>
#include <cstdarg>
#include <cstdio>
#include <stdlib.h>
#include "text_graphic.h"
#include "tweet_graphic.h"

const u32 TweetGraphic::bgClr = C2D_Color32(0xE3, 0xF1, 0xFC, 0xFF);

TweetGraphic::TweetGraphic(Tweet *tweet, float xStart, float yStart)
{
    this->tweet = tweet;
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

Tweet *TweetGraphic::getTweet()
{
    return this->tweet;
}

void TweetGraphic::draw()
{

    TextGraphic tweetTextGraphic =
        TextGraphic((this->tweet)->text,
                    300,
                    C2D_AlignLeft | C2D_WordWrap,
                    this->xStart + 5,
                    this->yStart + 5,
                    0,
                    0.5f,
                    0.5f);

    // Set tweet container height and width to fit tweet content
    tweetTextGraphic.getDimensions(&this->width, &this->height);
    this->height = (this->height * (tweetTextGraphic.getC2DText().width / 1569)) + 30;
    this->width = GSP_SCREEN_HEIGHT_TOP - 40;

    // Initialize fav count text
    char favCountBuf[7];
    sprintf(favCountBuf, "%d", (this->tweet)->favCount);
    const char *favCount = favCountBuf;

    TextGraphic favTextGraphic =
        TextGraphic(favCount,
                    7,
                    C2D_AlignLeft,
                    this->xStart + this->width - 30,
                    this->yStart + this->height - 15,
                    0,
                    0.5f,
                    0.5f);

    // Draw tweet container
    C2D_DrawRectSolid(this->xStart,
                      this->yStart,
                      0,
                      this->width,
                      this->height,
                      this->bgClr);

    // Draw text within tweet container and add word wrap with a padding of 5.
    tweetTextGraphic.draw(this->width - 5);

    // Draw fav text
    favTextGraphic.draw();
}
