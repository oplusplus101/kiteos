#ifndef __KITEOS__DRIVERS__DRIVER_H
#define __KITEOS__DRIVERS__DRIVER_H

namespace kiteos
{

    namespace drivers
    {

        class Driver
        {
        public:
            Driver();
            ~Driver();

            virtual void Activate();
            virtual int Reset();
            virtual void Deactivate();
        };

        class DriverManager
        {
        private:
            Driver *drivers[255];
            int numDrivers;

        public:
            DriverManager();
            ~DriverManager();

            void AddDriver(Driver *);
            void ActivateAll();
        };
    } // namespace drivers
} // namespace kiteos
#endif