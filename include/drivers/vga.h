
#ifndef __KITEOS__DRIVERS__VGA_H
#define __KITEOS__DRIVERS__VGA_H

#include <common/types.h>
#include <hardwarecommunication/port.h>

namespace kiteos
{
    namespace drivers
    {
        enum Color
        {
            TRANSPARENT = -0x01,
            BLACK = 0x00,
            BLUE = 0x01,
            GREEN = 0x02,
            CYAN = 0x03,
            RED = 0x04,
            MAGENTA = 0x05,
            BROWN = 0x06,
            BRIGHT_GRAY = 0x07,
            DARK_GRAY = 0x08,
            BRIGHT_BLUE = 0x09,
            BRIGHT_GREEN = 0x0A,
            BRIGHT_CYAN = 0x0B,
            BRIGHT_RED = 0x0C,
            BRIGHT_MAGENTA = 0x0D,
            YELLOW = 0x0E,
            WHITE = 0x0F
        };

        class VideoGraphicsArray
        {
        protected:
            hardwarecommunication::Port8Bit miscPort;
            hardwarecommunication::Port8Bit crtcIndexPort;
            hardwarecommunication::Port8Bit crtcDataPort;
            hardwarecommunication::Port8Bit sequencerIndexPort;
            hardwarecommunication::Port8Bit sequencerDataPort;
            hardwarecommunication::Port8Bit graphicsControllerIndexPort;
            hardwarecommunication::Port8Bit graphicsControllerDataPort;
            hardwarecommunication::Port8Bit attributeControllerIndexPort;
            hardwarecommunication::Port8Bit attributeControllerReadPort;
            hardwarecommunication::Port8Bit attributeControllerWritePort;
            hardwarecommunication::Port8Bit attributeControllerResetPort;

            void WriteRegisters(common::uint8_t *registers);
            common::uint8_t *GetFrameBufferSegment();

            virtual common::uint8_t GetColorIndex(common::uint8_t r, common::uint8_t g, common::uint8_t b);

        public:
            common::int32_t width, height, bpp;

            VideoGraphicsArray();
            ~VideoGraphicsArray();

            virtual bool SupportsMode(common::uint32_t width, common::uint32_t height, common::uint32_t colordepth);
            virtual bool SetMode(common::uint32_t width, common::uint32_t height, common::uint32_t colordepth);
            virtual void PutPixel(common::int32_t x, common::int32_t y, common::uint8_t colorIndex);
            virtual common::uint8_t GetPixel(common::int32_t x, common::int32_t y);
            virtual void DrawChar(char chr, common::int32_t x, common::int32_t y, common::uint8_t fgcolor);
            virtual void DrawText(char *text, common::int32_t x, common::int32_t y, common::uint8_t fgcolor);

            void FillRect(common::int32_t x, common::int32_t y, common::int32_t width, common::int32_t height, common::uint8_t color);
            
        };
    } // namespace drivers
} // namespace kiteos

#endif