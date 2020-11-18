#ifndef __KITEOS__COMMON__OSUTIL_H
#define __KITEOS__COMMON__OSUTIL_H

#include <common/types.h>

namespace kiteos
{
    namespace common
    {
        uint32_t FromMegaBytes(uint16_t mb);
        void memcpy(void *source, void *dest, common::int32_t size);

        void delay(uint32_t ms);

        void outb(uint16_t port, uint8_t val);
        uint8_t inb(uint16_t port);
    } // namespace common
} // namespace kiteos

#endif