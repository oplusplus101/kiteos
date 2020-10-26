
#include <drivers/dbrenderer.h>

using namespace kiteos::drivers;
using namespace kiteos::common;
using namespace kiteos;

DoubleBufferedRenderer::DoubleBufferedRenderer(int32_t width, int32_t height, uint8_t colorDepth)
{
    pixelStride = (colorDepth | 7) >> 3;
    pitch = scrW * pixelStride;

    scrW = width;
    scrH = height;
    bpp = colorDepth;

    vidmem = ((uint8_t *) 0xA0000);
	// BackBuffer = ((byte *) (malloc(ScreenHeight * Pitch)));
    for (int32_t y = 0; y < scrH; y++)
    {
        for (int32_t x = 0; x < scrW; x++)
        {
            backbuf[scrW * y + x] = 0;
        }
    }
}

DoubleBufferedRenderer::~DoubleBufferedRenderer()
{

}

void DoubleBufferedRenderer::PutPixel(int32_t x, int32_t y, uint8_t color)
{
    if (x < 0 || x >= scrW || y < 0 || y >= scrH)
        return;
    vidmem[(y << 8)+(y << 6) + x] = color;
}

void DoubleBufferedRenderer::SwapBuffers()
{
    // memcpy(backbuf, vidmem, scrH * pitch);
}
