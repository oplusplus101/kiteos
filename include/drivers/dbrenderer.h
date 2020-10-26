#ifndef __KITEOS__DRIVERS__DB_RENDERER_H
#define __KITEOS__DRIVERS__DB_RENDERER_H

#include <drivers/vga.h>
#include <common/types.h>
#include <common/osutil.h>

namespace kiteos
{
    namespace drivers
    {
        class DoubleBufferedRenderer
        {
            common::uint8_t *vidmem;
            common::uint8_t *backbuf;
            common::int32_t pitch, pixelStride, bpp;

            common::int32_t scrW, scrH;

        public:
            DoubleBufferedRenderer(common::int32_t width, common::int32_t height, common::uint8_t colorDepth);
            ~DoubleBufferedRenderer();

            virtual void SwapBuffers();

            virtual void PutPixel(common::int32_t x, common::int32_t y, common::uint8_t color);
        };
    } // namespace drivers

} // namespace kiteos

#endif
