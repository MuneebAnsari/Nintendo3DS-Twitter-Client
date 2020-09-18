#ifndef TIMELINE_H
#define TIMELINE_H

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <vector>
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
    std::vector<int> tweetsPerPage;

    void showPreviousPage();
    void resetFrame();

public:
    Timeline();
    Timeline(Tweet **head, C3D_RenderTarget *target);
    int &getPageNum();
    void scrollDown();
    void scrollUp();
    void draw();
};

#endif