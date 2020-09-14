#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <sys/types.h>
#include <cstdarg>
#include <cstdio>
#include <stdlib.h>
#include <vector>
#include "tweet_graphic.h"
#include "models.h"
#include "timeline.h"

Timeline::Timeline(Tweet **head, C3D_RenderTarget *target)
{
    this->head = *head;
    this->last = (this->head)->prev;
    this->target = target;
    this->screenSpace = GSP_SCREEN_HEIGHT_TOP;
    this->xs = 20;
    this->ys = 20;
    this->pageNum = 1;
}

void Timeline::scrollDown()
{
    if (this->screenSpace <= 0 && this->head != NULL)
    {
        this->tweetsPerPage.insert(
            this->tweetsPerPage.begin() + (this->pageNum - 1),
            this->numTweetsOnPage);
        this->pageNum++;
        this->resetFrame();
        this->numTweetsOnPage = 0;
    }
}

void Timeline::scrollUp()
{
    if (this->pageNum > 1)
    {
        this->pageNum--;
        this->resetFrame();
        this->showPreviousPage();
        this->numTweetsOnPage = 0;
    }
}

void Timeline::draw()
{

    while (this->head != NULL)
    {
        TweetGraphic currTweetGraphic = TweetGraphic(this->head, this->xs, this->ys);

        if (this->screenSpace > 0)
        {
            currTweetGraphic.draw();
            this->numTweetsOnPage++;
            this->ys = this->ys + currTweetGraphic.getHeight() + 10;
            this->screenSpace -= this->ys;
            this->last = this->head;
            this->head = (this->head)->next;
        }
        else
        {

            break;
        }
    }
}

void Timeline::resetFrame()
{
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
    // clear screen contents
    C2D_TargetClear(this->target, C2D_Color32(0x00, 0xAC, 0xEE, 0xFF));
    C2D_SceneBegin(this->target);
    // reset screen space
    this->screenSpace = GSP_SCREEN_HEIGHT_TOP;
    // reset frame start position
    this->xs = 20;
    this->ys = 20;
}

void Timeline::showPreviousPage()
{
    int i = 1;
    int numTweetsOnPrevPage = this->tweetsPerPage.at(this->pageNum - 1);
    while ((i < this->numTweetsOnPage + numTweetsOnPrevPage) && (this->last)->prev != NULL)
    {
        i++;
        this->last = (this->last)->prev;
    }
    this->head = (this->last);
}