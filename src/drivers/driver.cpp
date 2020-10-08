#include <drivers/driver.h>

using namespace kiteos;
using namespace kiteos::drivers;

Driver::Driver()
{
}

Driver::~Driver()
{
}

void Driver::Activate()
{
}

int Driver::Reset()
{
    return 0;
}

void Driver::Deactivate()
{
}

DriverManager::DriverManager()
{
}

DriverManager::~DriverManager()
{
}

void DriverManager::AddDriver(Driver *drv)
{
    drivers[numDrivers] = drv;
    numDrivers++;
}

void DriverManager::ActivateAll()
{
    for (int i = 0; i < numDrivers; i++)
        drivers[i]->Activate();    
}