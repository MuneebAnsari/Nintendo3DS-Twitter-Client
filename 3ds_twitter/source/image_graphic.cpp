#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>
#include <tex3ds.h>
#include <sys/types.h>
#include "image_graphic.h"

ImageGraphic::ImageGraphic(C2D_Image *img)
{
    this->img = img;
}

void ImageGraphic::applyTexture(C3D_Tex *tex, const char *t3xPath, u16 texWidth, u16 texHeight)
{

    Tex3DS_SubTexture *subtex = new Tex3DS_SubTexture();

    subtex->left = 0;
    subtex->top = 0;
    subtex->right = 1;
    subtex->bottom = 1;

    subtex->width = texWidth;
    subtex->height = texHeight;

    (this->img)->subtex = subtex;
    (this->img)->tex = tex;

    FILE *fd = fopen(t3xPath, "rb");
    if (!fd)
    {
        printf("fail open tex\n");
    }

    Tex3DS_Texture t3x = Tex3DS_TextureImportStdio(fd, tex, NULL, false);

    C3D_TexSetFilter(tex, GPU_LINEAR, GPU_NEAREST);
    Tex3DS_TextureFree(t3x);
}