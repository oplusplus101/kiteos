
#include <hardwarecommunication/pci.h>

using namespace kiteos::hardwarecommunication;
using namespace kiteos::common;
using namespace kiteos::drivers;

void printf(wchar_t *str);
void printHexf(uint8_t key);

PeripheralComponentInterconnectDeviceDescriptor::PeripheralComponentInterconnectDeviceDescriptor()
{
	
}

PeripheralComponentInterconnectDeviceDescriptor::~PeripheralComponentInterconnectDeviceDescriptor()
{
	
}

PeripheralComponentInterconnectController::PeripheralComponentInterconnectController()
	: dataPort(0xCFC),
	  commandPort(0xCF8)
{
}

PeripheralComponentInterconnectController::~PeripheralComponentInterconnectController()
{
}

int32_t PeripheralComponentInterconnectController::Read(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset)
{
	uint32_t id =
		0x1 << 31 | ((bus & 0xFF) << 16) | ((device & 0x1F) << 11) | ((function & 0x07) << 8) | (registeroffset & 0xFC);

	commandPort.Write(id);
	uint32_t result = dataPort.Read();
	return result >> (8 * (registeroffset % 4));
}

void PeripheralComponentInterconnectController::Write(uint16_t bus, uint16_t device, uint16_t function, uint32_t registeroffset, uint32_t value)
{
	uint32_t id =
		0x1 << 31 | ((bus & 0xFF) << 16) | ((device & 0x1F) << 11) | ((function & 0x07) << 8) | (registeroffset & 0xFC);
	commandPort.Write(id);
	dataPort.Write(value);
}

bool PeripheralComponentInterconnectController::DeviceHasFunctions(uint16_t bus, uint16_t device)
{
	return Read(bus, device, 0, 0x0E) & (1 << 7);
}

void PeripheralComponentInterconnectController::SelectDrivers(DriverManager *driverManager, InterruptManager *interrupts)
{
	for (int bus = 0; bus < 8; bus++)
	{
		for (int device = 0; device < 32; device++)
		{
			uint8_t numFunctions = DeviceHasFunctions(bus, device) ? 8 : 1;
			for (int function = 0; function < numFunctions; function++)
			{
				PeripheralComponentInterconnectDeviceDescriptor dev = GetDeviceDescriptor(bus, device, function);

				if (dev.vendor_id == 0x0000 || dev.vendor_id == 0xFFFF)
					continue;

				for (int barNum = 0; barNum < 6; barNum++)
				{
					BaseAddressRegister bar = GetBaseAddressRegister(bus, device, function, barNum)
				}
				

				printf(L"PCI BUS ");
				printHexf(bus & 0xFF);
				
				printf(L", DEVICE ");
				printHexf(device & 0xFF);
				
				printf(L", FUNCTION ");
				printHexf(function & 0xFF);
				
				printf(L" = VENDOR ");
				printHexf((dev.vendor_id & 0xFF00) >> 8);
				printHexf(dev.vendor_id & 0xFF);

				printf(L", DEVICE ");
				printHexf((dev.device_id & 0xFF00) >> 8);
				printHexf(dev.device_id & 0xFF);

				printf(L"\n");
			}
		}
	}
}

PeripheralComponentInterconnectDeviceDescriptor PeripheralComponentInterconnectController::GetDeviceDescriptor(uint16_t bus, uint16_t device, uint16_t function)
{
    PeripheralComponentInterconnectDeviceDescriptor result;
    
    result.bus = bus;
    result.device = device;
    result.function = function;
    
    result.vendor_id = Read(bus, device, function, 0x00);
    result.device_id = Read(bus, device, function, 0x02);

    result.class_id = Read(bus, device, function, 0x0b);
    result.subclass_id = Read(bus, device, function, 0x0a);
    result.interface_id = Read(bus, device, function, 0x09);

    result.revision = Read(bus, device, function, 0x08);
    result.interrupt = Read(bus, device, function, 0x3c);
    
    return result;
}
