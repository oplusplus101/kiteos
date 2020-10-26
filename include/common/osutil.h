#ifndef __KITEOS__COMMON__OSUTIL_H
#define __KITEOS__COMMON__OSUTIL_H

#include <common/types.h>

namespace kiteos
{
    namespace common
    {
        uint32_t FromMegaBytes(uint16_t mb);
        void memcpy(void *source, void *dest, common::int32_t size);
    } // namespace std
} // namespace kiteos

#endif