#ifndef IMAGE_GRAPHIC_H
#define IMAGE_GRAPHIC_H

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <sys/types.h>

class ImageGraphic
{
private:
    C2D_Image *img;

public:
    ImageGraphic(C2D_Image *img);

    void applyTexture(C3D_Tex *tex, const char *t3xPath, u16 texWidth, u16 texHeight);
};
#endif