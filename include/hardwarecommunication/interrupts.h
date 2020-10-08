#ifndef __KITEOS__HARDWARECOMMUNICATION__INTERUPTS_H
#define __KITEOS__HARDWARECOMMUNICATION__INTERUPTS_H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <gdt.h>

namespace kiteos
{
    namespace hardwarecommunication
    {

        class InterruptManager;

        class InterruptHandler
        {
        protected:
            kiteos::common::uint8_t interruptNumber;
            InterruptManager *interruptManager;
            InterruptHandler(kiteos::common::uint8_t interruptNumber, InterruptManager *interruptManager);
            ~InterruptHandler();

        public:
            virtual kiteos::common::uint32_t HandleInterrupt(kiteos::common::uint32_t esp);
        };

        class InterruptManager
        {
            friend class InterruptHandler;

        protected:
            static InterruptManager *ActiveInteruptManager;
            InterruptHandler *handlers[256];

            struct GateDescriptor
            {
                kiteos::common::uint16_t handlerAddressLowBits;
                kiteos::common::uint16_t gdt_codeSegmentSelector;
                kiteos::common::uint8_t reserved;
                kiteos::common::uint8_t access;
                kiteos::common::uint16_t handlerAddressHighBits;

            } __attribute__((packed));

            static GateDescriptor interruptDescriptorTable[256];

            struct InterruptDescriptorTablePointer
            {
                kiteos::common::uint16_t size;
                kiteos::common::uint32_t base;
            } __attribute__((packed));

            static void SetInterruptDescriptorTableEntry(kiteos::common::uint8_t interrupt,
                                                         kiteos::common::uint16_t codeSegmentSelectorOffset, void (*handler)(),
                                                         kiteos::common::uint8_t DescriptorPrivilegeLevel, kiteos::common::uint8_t DescriptorType);

            Port8BitSlow picMasterCommand;
            Port8BitSlow picMasterData;
            Port8BitSlow picSlaveCommand;
            Port8BitSlow picSlaveData;

        public:
            InterruptManager(GlobalDescriptorTable *gdt);
            ~InterruptManager();

            void Activate();
            void Deactivate();

            static kiteos::common::uint32_t handleInterrupt(kiteos::common::uint8_t interuptNumber, kiteos::common::uint32_t esp);
            kiteos::common::uint32_t DoHandleInterrupt(kiteos::common::uint8_t interuptNumber, kiteos::common::uint32_t esp);

            static void IgnoreInterruptRequest();

            static void HandleInterruptRequest0x00();
            static void HandleInterruptRequest0x01();
            static void HandleInterruptRequest0x02();
            static void HandleInterruptRequest0x03();
            static void HandleInterruptRequest0x04();
            static void HandleInterruptRequest0x05();
            static void HandleInterruptRequest0x06();
            static void HandleInterruptRequest0x07();
            static void HandleInterruptRequest0x08();
            static void HandleInterruptRequest0x09();
            static void HandleInterruptRequest0x0A();
            static void HandleInterruptRequest0x0B();
            static void HandleInterruptRequest0x0C();
            static void HandleInterruptRequest0x0D();
            static void HandleInterruptRequest0x0E();
            static void HandleInterruptRequest0x0F();
            static void HandleInterruptRequest0x31();

            static void HandleException0x00();
            static void HandleException0x01();
            static void HandleException0x02();
            static void HandleException0x03();
            static void HandleException0x04();
            static void HandleException0x05();
            static void HandleException0x06();
            static void HandleException0x07();
            static void HandleException0x08();
            static void HandleException0x09();
            static void HandleException0x0A();
            static void HandleException0x0B();
            static void HandleException0x0C();
            static void HandleException0x0D();
            static void HandleException0x0E();
            static void HandleException0x0F();
            static void HandleException0x10();
            static void HandleException0x11();
            static void HandleException0x12();
            static void HandleException0x13();
        };

    } // namespace hardwarecommunication

} // namespace kiteos
#endif
