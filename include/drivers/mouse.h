#ifndef __KITEOS__DRIVERS__MOUSE_H
#define __KITEOS__DRIVERS__MOUSE_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>

namespace kiteos
{

    namespace drivers
    {
        class MouseEventHandler
        {

        public:
            MouseEventHandler();
            virtual void OnActivate();
            virtual void OnMouseDown(kiteos::common::uint8_t);
            virtual void OnMouseUp(kiteos::common::uint8_t);
            virtual void OnMouseMove(kiteos::common::int8_t, kiteos::common::int8_t);
        };

        class MouseDriver : public kiteos::hardwarecommunication::InterruptHandler, public Driver
        {
            kiteos::hardwarecommunication::Port8Bit dataport;
            kiteos::hardwarecommunication::Port8Bit commandport;

            kiteos::common::uint8_t buffer[3];
            kiteos::common::uint8_t offset;
            kiteos::common::uint8_t buttons;

            MouseEventHandler *handler;

        public:
            MouseDriver(kiteos::hardwarecommunication::InterruptManager *interruptManager, MouseEventHandler *handler);
            ~MouseDriver();

            virtual kiteos::common::uint32_t HandleInterrupt(kiteos::common::uint32_t esp);
            virtual void Activate();
        };
    } // namespace drivers
} // namespace kiteos
#endif
