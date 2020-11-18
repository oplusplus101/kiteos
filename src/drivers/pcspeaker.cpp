
#include <drivers/pcspeaker.h>

using namespace kiteos::common;
using namespace kiteos::drivers;

PCSpeaker::PCSpeaker()
    : Driver()
{
}

PCSpeaker::~PCSpeaker()
{
}

void PCSpeaker::Play(uint32_t frequency)
{
    uint32_t Div;
    uint8_t tmp;

    //Set the PIT to the desired frequency
    Div = 1193180 / frequency;
    outb(0x43, 0xb6);
    outb(0x42, (uint8_t)(Div));
    outb(0x42, (uint8_t)(Div >> 8));

    //And play the sound using the PC speaker
    tmp = inb(0x61);
    if (tmp != (tmp | 3))
    {
        outb(0x61, tmp | 3);
    }
}

void PCSpeaker::Stop()
{
    uint8_t tmp = inb(0x61) & 0xFC;
 
 	outb(0x61, tmp);
}

void PCSpeaker::Beep()
{
    Play(100);
    delay(1000);
    Stop();
}

void PCSpeaker::PlaySong(char *notes)
{
    for (int i = 0; notes[i] != '\0'; i++)
    {
        char note = notes[i];
        if (note == 'C')
            Play(65);
        else if (note == 'E')
            Play(82);
        else if (note == 'F')
            Play(87);
        else if (note == 'G')
            Play(98);
        else if (note == 'A')
            Play(110);
        else if (note == 'B')
            Play(123);
        else if (note == 'P')
            delay(5000);
        Stop();
    }
    
}

void PCSpeaker::Activate()
{
}
