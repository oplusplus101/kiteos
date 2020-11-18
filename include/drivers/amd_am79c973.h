#ifndef __KITEOS__DRIVERS__AMD_AM79C973_H
#define __KITEOS__DRIVERS__AMD_AM79C973_H

#include <hardwarecommunication/pci.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>
#include <types.h>

namespace kiteos
{
    namespace drivers
    {
        class amd_am79c973 : public Driver, hardwarecommunication::InterruptHandler
        {
            hardwarecommunication::Port16Bit MACAddress0Port;
            hardwarecommunication::Port16Bit MACAddress2Port;
            hardwarecommunication::Port16Bit MACAddress4Port;
            hardwarecommunication::Port16Bit registerDataPort;
            hardwarecommunication::Port16Bit registerAddressPort;
            hardwarecommunication::Port16Bit resetPort;
            hardwarecommunication::Port16Bit busControlRegisterDataPort;

            InitializationBlock initBlock;

        public:
            amd_am79c973(hardwarecommunication::PeripheralComponentInterconnectController dev, hardwarecommunication::InterruptManager *interrupts);
            ~amd_am79c973();
        };
    } // namespace drivers

} // namespace kiteos

#endif
