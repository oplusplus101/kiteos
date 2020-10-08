
#ifndef __KITEOS__DRIVERS__KEYBOARD_H
#define __KITEOS__DRIVERS__KEYBOARD_H

#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>
#include <drivers/driver.h>

namespace kiteos
{

    namespace drivers
    {

        class KeyboardEventHandler
        {
        public:
            KeyboardEventHandler();
            virtual void OnKeyDown(wchar_t *keydata, kiteos::common::uint8_t keyid);
            virtual void OnKeyUp(wchar_t *keydata, kiteos::common::uint8_t keyid);
        };

        class KeyboardDriver : public kiteos::hardwarecommunication::InterruptHandler,
                               public Driver
        {
            kiteos::hardwarecommunication::Port8Bit dataport;
            kiteos::hardwarecommunication::Port8Bit commandport;

            KeyboardEventHandler *handler;

        public:
            KeyboardDriver(kiteos::hardwarecommunication::InterruptManager *interruptManager, KeyboardEventHandler *handler);
            ~KeyboardDriver();

            virtual kiteos::common::uint32_t HandleInterrupt(kiteos::common::uint32_t esp);
            virtual void Activate();
        };
    } // namespace drivers
} // namespace kiteos

#endif
