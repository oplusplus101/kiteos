#ifndef __KITEOS__HARDWARECOMMUNICATION__PORT_H
#define __KITEOS__HARDWARECOMMUNICATION__PORT_H

#include <common/types.h>

namespace kiteos
{
    namespace hardwarecommunication
    {

        class Port
        {
        protected:
            kiteos::common::uint16_t portnumber;
            Port(kiteos::common::uint16_t portnumber);
            ~Port();
        };

        class Port8Bit : public Port
        {
        public:
            Port8Bit(kiteos::common::uint16_t portnumber);
            ~Port8Bit();

            virtual void Write(kiteos::common::uint8_t data);
            virtual kiteos::common::uint8_t Read();
        };

        class Port8BitSlow : public Port8Bit
        {
        public:
            Port8BitSlow(kiteos::common::uint16_t portnumber);
            ~Port8BitSlow();

            virtual void Write(kiteos::common::uint8_t data);
        };

        class Port16Bit : public Port
        {
        public:
            Port16Bit(kiteos::common::uint16_t portnumber);
            ~Port16Bit();

            virtual void Write(kiteos::common::uint16_t data);
            virtual kiteos::common::uint16_t Read();
        };

        class Port32Bit : public Port
        {
        public:
            Port32Bit(kiteos::common::uint16_t portnumber);
            ~Port32Bit();

            virtual void Write(kiteos::common::uint32_t data);
            virtual kiteos::common::uint32_t Read();
        };
    } // namespace hardwarecommunication
} // namespace kiteos

#endif