#include <common/osutil.h>

using namespace kiteos::common;

uint32_t kiteos::common::FromMegaBytes(uint16_t mb)
{
    return mb * 1024 * 1024;
}

void kiteos::common::memcpy(void *source, void *dest, int32_t size)
{
    //cast src and dest to char*
    char *src_char = (char *)source;
    char *dest_char = (char *)dest;
    for (int i = 0; i < size; i++)
        dest_char[i] = src_char[i];
}

void kiteos::common::delay(uint32_t ms)
{
    uint32_t i = 0;
    while (i <= ms)
    {
        i++;
    }
}


void kiteos::common::outb(uint16_t port, uint8_t val)
{
    asm volatile("outb %0, %1"
                 :
                 : "a"(val), "Nd"(port));
}

uint8_t kiteos::common::inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0"
                 : "=a"(ret)
                 : "Nd"(port));
    
    return ret;
}
