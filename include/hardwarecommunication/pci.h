#ifndef __KITEOS__HARDWARECOMMUNICATION__PCI__H
#define __KITEOS__HARDWARECOMMUNICATION__PCI__H

#include <common/types.h>
#include <hardwarecommunication/port.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/driver.h>
#include <hardwarecommunication/interrupts.h>

namespace kiteos
{
    namespace hardwarecommunication
    {

        enum BaseAdderssRegisterType
        {
            MemoryMapping = 0,
            InputOutput = 1
        };

        class BaseAddressRegister
        {
        public:
            bool prefetchable;
            kiteos::common::uint8_t *address;
            kiteos::common::uint32_t size;
            BaseAdderssRegisterType type;
        };

        class PeripheralComponentInterconnectDeviceDescriptor
        {
        public:
            kiteos::common::uint32_t portBase;
            kiteos::common::uint32_t interrupt;

            kiteos::common::uint16_t bus;
            kiteos::common::uint16_t device;
            kiteos::common::uint16_t function;

            kiteos::common::uint16_t vendor_id;
            kiteos::common::uint16_t device_id;

            kiteos::common::uint8_t class_id;
            kiteos::common::uint8_t subclass_id;
            kiteos::common::uint8_t interface_id;
            kiteos::common::uint8_t revision;

            PeripheralComponentInterconnectDeviceDescriptor();
            ~PeripheralComponentInterconnectDeviceDescriptor();
        };

        class PeripheralComponentInterconnectController
        {

            Port32Bit dataPort;
            Port32Bit commandPort;

        public:
            PeripheralComponentInterconnectController();
            ~PeripheralComponentInterconnectController();

            kiteos::common::int32_t Read(kiteos::common::uint16_t bus, kiteos::common::uint16_t device, kiteos::common::uint16_t function, kiteos::common::uint32_t registeroffset);
            void Write(kiteos::common::uint16_t bus, kiteos::common::uint16_t device, kiteos::common::uint16_t function, kiteos::common::uint32_t registeroffset, kiteos::common::uint32_t value);
            bool DeviceHasFunctions(kiteos::common::uint16_t bus, kiteos::common::uint16_t device);

            void SelectDrivers(kiteos::drivers::DriverManager *driverManager, kiteos::hardwarecommunication::InterruptManager *interrupts);
            PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(kiteos::common::uint16_t bus, kiteos::common::uint16_t device, kiteos::common::uint16_t function);
            BaseAddressRegister GetBaseAddressRegister(kiteos::common::uint16_t bus, kiteos::common::uint16_t device, kiteos::common::uint16_t function,kiteos::common::uint16_t bar);
        };
    } // namespace hardwarecommunication

} // namespace kiteos

#endif