#ifndef __KITEOS__COMMON__OSUTIL_H
#define __KITEOS__COMMON__OSUTIL_H

#include <common/types.h>

namespace kiteos
{
    namespace common
    {

        uint32_t fromMegaBytes(uint16_t mb)
        {
            return mb * 1024 * 1024;
        }

    } // namespace std
} // namespace kiteos

#endif