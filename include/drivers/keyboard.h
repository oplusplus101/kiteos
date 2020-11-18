
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
            virtual void OnKeyDown(char *keydata, common::uint8_t keyid);
            virtual void OnKeyUp(char *keydata, common::uint8_t keyid);
        };

        class KeyboardDriver : public hardwarecommunication::InterruptHandler,
                               public Driver
        {
            hardwarecommunication::Port8Bit dataport;
            hardwarecommunication::Port8Bit commandport;

            KeyboardEventHandler *handler;

        public:
            KeyboardDriver(hardwarecommunication::InterruptManager *interruptManager, KeyboardEventHandler *handler);
            ~KeyboardDriver();

            virtual common::uint32_t HandleInterrupt(common::uint32_t esp);
            virtual void Activate();
        };
    } // namespace drivers
} // namespace kiteos

#endif
