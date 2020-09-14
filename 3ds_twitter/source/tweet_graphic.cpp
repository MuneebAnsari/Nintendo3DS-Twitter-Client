#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <sys/types.h>
#include <cstdarg>
#include <cstdio>
#include <stdlib.h>
#include "text_graphic.h"
#include "image_graphic.h"
#include "tweet_graphic.h"

const u32 TweetGraphic::bgClr = C2D_Color32(0xE3, 0xF1, 0xFC, 0xFF);

TweetGraphic::TweetGraphic(Tweet *tweet, float xStart, float yStart)
{
    this->tweet = tweet;
    this->xStart = xStart;
    this->yStart = yStart;
    this->initBounds();
}

float &TweetGraphic::getHeight()
{
    return this->height;
}

float &TweetGraphic::getWidth()
{
    return this->width;
}

Tweet &TweetGraphic::getTweet()
{
    return *this->tweet;
}

void TweetGraphic::draw()
{
    // Initialize fav count text
    char favCountBuf[7];
    sprintf(favCountBuf, "%d", (this->tweet)->favCount);
    const char *favCount = favCountBuf;

    TextGraphic favCountTextGraphic =
        TextGraphic(favCount,
                    7,
                    C2D_AlignLeft,
                    this->xStart + this->width - 40,
                    this->yStart + this->height - 15,
                    0,
                    0.5f,
                    0.5f);

    //Initialize fav graphic
    C2D_Image heart;
    C3D_Tex heartTex;
    ImageGraphic favHeartGraphic = ImageGraphic(&heart);
    favHeartGraphic.applyTexture(&heartTex, "romfs:/gfx/heart.t3x", 16, 16);

    // Draw tweet container
    C2D_DrawRectSolid(this->xStart,
                      this->yStart,
                      0,
                      this->width,
                      this->height,
                      this->bgClr);

    // Draw text within tweet container and add word wrap with a padding of 5.
    float wordWrap = this->width - 5;
    this->tweetTextGraphic.draw(wordWrap);

    // Draw fav heart graphic
    C2D_DrawImageAt(heart, this->xStart + this->width - 20, this->yStart + this->height - 20, 0);

    // Draw fav count text
    favCountTextGraphic.draw();
}

void TweetGraphic::initBounds()
{
    // Initialize tweet text
    this->tweetTextGraphic =
        TextGraphic((this->tweet)->text,
                    300,
                    C2D_AlignLeft | C2D_WordWrap,
                    this->xStart + 5,
                    this->yStart + 5,
                    0,
                    0.5f,
                    0.5f);

    //Set tweet container height and width to fit tweet content
    this->tweetTextGraphic.getDimensions(&this->width, &this->height);
    this->height = (this->height * (this->tweetTextGraphic.getC2DText().width / 1569)) + 30;
    this->width = GSP_SCREEN_HEIGHT_TOP - 40;
}
