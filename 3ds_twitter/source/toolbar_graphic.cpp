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
#include "toolbar_graphic.h"

ToolbarGraphic::ToolbarGraphic(float xStart, float yStart)
{

    this->xStart = xStart;
    this->yStart = yStart;
}

void ToolbarGraphic::draw()
{
    float w = GSP_SCREEN_HEIGHT_BOTTOM;
    float h = 25;

    TextGraphic footerText =
        TextGraphic("Created By: Muneeb Ansari",
                    sizeof("Created By: Muneeb Ansari"),
                    C2D_AlignCenter,
                    (this->xStart + w) / 2,
                    (this->yStart + (h / 2)),
                    0,
                    0.5f,
                    0.5f);

    C2D_DrawRectSolid(this->xStart,
                      this->yStart,
                      0,
                      this->xStart + w,
                      this->yStart + h,
                      C2D_Color32(0xff, 0xff, 0xff, 0xff));

    footerText.draw();
}