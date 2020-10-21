#include <common/osutil.h>

using namespace kiteos::common;

uint32_t FromMegaBytes(uint16_t mb)
{
    return mb * 1024 * 1024;
}
