
#ifndef __KITEOS__DRIVERS__PCSPEAKER_H
#define __KITEOS__DRIVERS__PCSPEAKER_H

#include <drivers/driver.h>
#include <common/osutil.h>
#include <common/types.h>

namespace kiteos
{
    namespace drivers
    {
        class PCSpeaker : public Driver
        {
        private:
        public:
            PCSpeaker();
            ~PCSpeaker();

            void Play(common::uint32_t frequency);
            void Stop();

            void Beep();

            void PlaySong(char *notes);


        private:
            virtual void Activate();
        };

    } // namespace drivers

} // namespace kiteos
#endif