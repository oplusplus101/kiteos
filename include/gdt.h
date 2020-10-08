#include <common/types.h>

#ifndef __GDT_H
#define __GDT_H

class GlobalDescriptorTable
{
public:
    class SegmentDescriptor
    {
    private:
        kiteos::common::uint16_t limit_lo;
        kiteos::common::uint16_t base_lo;
        kiteos::common::uint8_t base_hi;
        kiteos::common::uint8_t type;
        kiteos::common::uint8_t flags_limit_hi;
        kiteos::common::uint8_t base_vhi;

    public:
        SegmentDescriptor(kiteos::common::uint32_t base, kiteos::common::uint32_t limit, kiteos::common::uint8_t type);
        kiteos::common::uint32_t Base();
        kiteos::common::uint32_t Limit();

    } __attribute__((packed));

    SegmentDescriptor nullSegmentSelector;
    SegmentDescriptor unusedSegmentSelector;
    SegmentDescriptor codeSegmentSelector;
    SegmentDescriptor dataSegmentSelector;

public:
    GlobalDescriptorTable();
    ~GlobalDescriptorTable();

    kiteos::common::uint16_t CodeSegmentSelector();
    kiteos::common::uint16_t DataSegmentSelector();
};

#endif