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
            common::uint8_t *address;
            common::uint32_t size;
            BaseAdderssRegisterType type;
        };

        class PeripheralComponentInterconnectDeviceDescriptor
        {
        public:
            common::uint32_t portBase;
            common::uint32_t interrupt;

            common::uint16_t bus;
            common::uint16_t device;
            common::uint16_t function;

            common::uint16_t vendor_id;
            common::uint16_t device_id;

            common::uint8_t class_id;
            common::uint8_t subclass_id;
            common::uint8_t interface_id;
            common::uint8_t revision;

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

            common::int32_t Read(common::uint16_t bus, common::uint16_t device, common::uint16_t function, common::uint32_t registeroffset);
            void Write(common::uint16_t bus, common::uint16_t device, common::uint16_t function, common::uint32_t registeroffset, common::uint32_t value);
            bool DeviceHasFunctions(common::uint16_t bus, common::uint16_t device);

            void SelectDrivers(drivers::DriverManager *driverManager, hardwarecommunication::InterruptManager *interrupts);
            drivers::Driver *GetDriver(PeripheralComponentInterconnectDeviceDescriptor dev, hardwarecommunication::InterruptManager *interrupts);
            PeripheralComponentInterconnectDeviceDescriptor GetDeviceDescriptor(common::uint16_t bus, common::uint16_t device, common::uint16_t function);
            BaseAddressRegister GetBaseAddressRegister(common::uint16_t bus, common::uint16_t device, common::uint16_t function,common::uint16_t bar);
        };
    } // namespace hardwarecommunication

} // namespace kiteos

#endif