#include <iostream>
#include <string>
#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include "text_graphic.h"
#include "image_graphic.h"
#include "post_tweet_graphic.h"

PostTweetGraphic::PostTweetGraphic(float xStart, float yStart)
{
    this->xStart = xStart;
    this->yStart = yStart;
    this->tweetBuf.clear();
}

std::string PostTweetGraphic::updateWithText()
{
    char tmp[281];
    SwkbdState kbdState;
    SwkbdStatusData kbdStatus;
    SwkbdButton button = SWKBD_BUTTON_NONE;

    swkbdInit(&kbdState, SWKBD_TYPE_NORMAL, 2, 281);
    swkbdSetHintText(&kbdState, "What's happening?");
    swkbdSetButton(&kbdState, SWKBD_BUTTON_LEFT, "Cancel", false);
    swkbdSetButton(&kbdState, SWKBD_BUTTON_RIGHT, "Tweet", true);
    swkbdSetStatusData(&kbdState, &kbdStatus, false, true);
    button = swkbdInputText(&kbdState, tmp, sizeof(tmp));
    if (button != SWKBD_BUTTON_NONE)
    {
        std::string inpStr(tmp);
        this->tweetBuf = inpStr;
        this->post =
            TextGraphic(this->tweetBuf,
                        sizeof(tmp),
                        C2D_AlignLeft | C2D_WordWrap,
                        this->xStart + 10,
                        this->yStart + 10,
                        0,
                        0.45f,
                        0.45f);
    }
    return this->tweetBuf;
}

void PostTweetGraphic::clear()
{
    this->tweetBuf.clear();
    this->draw();
}

void PostTweetGraphic::draw()
{
    float w = GSP_SCREEN_HEIGHT_BOTTOM - 40;
    float h = GSP_SCREEN_WIDTH / 2;

    C2D_DrawRectSolid(this->xStart,
                      this->yStart,
                      0,
                      w,
                      h,
                      C2D_Color32(0xE3, 0xF1, 0xFC, 0xFF));

    if (this->tweetBuf.length() == 0)
    {

        TextGraphic initText =
            TextGraphic("What's happening?",
                        sizeof("What's happening?"),
                        C2D_AlignLeft,
                        this->xStart + 10,
                        this->yStart + 10,
                        0,
                        0.45f,
                        0.45f);

        initText.draw();
    }
    else if (this->tweetBuf.length() <= 281)
    {
        float wordWrap = this->xStart + w - 40;
        this->post.draw(wordWrap);
    }
    else
    {
        this->tweetBuf.clear();
    }
}
