#ifndef __KITEOS__COMMON__SPRITES_H
#define __KITEOS__COMMON__SPRITES_H

#include <common/types.h>
#include <drivers/vga.h>

namespace kiteos
{
    namespace common
    {
        #define WINDOW_BUTTON_CLOSE_WIDTH 4
        #define WINDOW_BUTTON_CLOSE_HEIGHT 4
        
        const uint8_t WINDOW_BUTTON_CLOSE[] = {
            drivers::BLACK, drivers::TRANSPARENT, drivers::TRANSPARENT, drivers::BLACK,//
            drivers::TRANSPARENT, drivers::BLACK, drivers::BLACK, drivers::TRANSPARENT,//
            drivers::TRANSPARENT, drivers::BLACK, drivers::BLACK, drivers::TRANSPARENT,//
            drivers::BLACK, drivers::TRANSPARENT, drivers::TRANSPARENT, drivers::BLACK
        };

        
    } // namespace common
    
} // namespace kiteos


#endif