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
#include "post_tweet_graphic.h"

PostTweetGraphic::PostTweetGraphic(float xStart, float yStart)
{
    this->xStart = xStart;
    this->yStart = yStart;
    memset(this->tweetBuf, 0, sizeof(this->tweetBuf));
}

void PostTweetGraphic::updateWithText()
{
    SwkbdState kbdState;
    SwkbdStatusData kbdStatus;
    SwkbdButton button = SWKBD_BUTTON_NONE;

    swkbdInit(&kbdState, SWKBD_TYPE_NORMAL, 2, 281);
    swkbdSetHintText(&kbdState, "What's happening?");
    swkbdSetButton(&kbdState, SWKBD_BUTTON_LEFT, "Cancel", false);
    swkbdSetButton(&kbdState, SWKBD_BUTTON_RIGHT, "Tweet", true);
    swkbdSetStatusData(&kbdState, &kbdStatus, false, true);
    button = swkbdInputText(&kbdState, this->tweetBuf, sizeof(this->tweetBuf));
    if (button != SWKBD_BUTTON_NONE)
    {
        this->post =
            TextGraphic(this->tweetBuf,
                        sizeof(this->tweetBuf),
                        C2D_AlignLeft | C2D_WordWrap,
                        this->xStart + 10,
                        this->yStart + 10,
                        0,
                        0.45f,
                        0.45f);
    }
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

    if (strlen(this->tweetBuf) == 0)
    {

        this->post =
            TextGraphic("What's happening?",
                        sizeof("What's happening?"),
                        C2D_AlignLeft,
                        this->xStart + 10,
                        this->yStart + 10,
                        0,
                        0.45f,
                        0.45f);

        this->post.draw();
    }
    else if (strlen(this->tweetBuf) <= 281)
    {
        this->post.draw(w - 15);
    }
    else
    {
        memset(this->tweetBuf, 0, 281);
    }
}
