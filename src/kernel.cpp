#include <gdt.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/driver.h>
#include <hardwarecommunication/pci.h>
#include <drivers/vga.h>

/*
\204 => ä
\224 => ö
\201 => ü
*/

using namespace kiteos;
using namespace kiteos::common;
using namespace kiteos::drivers;
using namespace kiteos::hardwarecommunication;

void printf(wchar_t *str)
{

    static uint16_t *VideoMemory = (uint16_t *)0xb8000;
    static int8_t x = 0, y = 0;

    static wchar_t *curTextOnScreen;

    auto WriteToVideoMemory = [&](wchar_t chr, int _x, int _y) {
        curTextOnScreen[80 * _y + _x] = chr;
        VideoMemory[80 * _y + _x] = (VideoMemory[80 * y + x] & 0xFF00) | chr;
    };

    for (int i = 0; str[i] != L'\0'; i++)
    {
        switch (str[i])
        {
        case L'\a':
            x--;
            if (x < 0)
            {
                if (y < 0)
                    y = 0;
                int i = 80;

                x = i;
                WriteToVideoMemory(0, x, y);
            }
            else
            {
                WriteToVideoMemory(0, x, y);
            }
            break;
        case L'ä':
            WriteToVideoMemory(L'\204', x, y);
            x++;
            break;
        case L'ö':
            WriteToVideoMemory(L'\224', x, y);
            x++;
            break;
        case L'ü':
            WriteToVideoMemory(L'\201', x, y);
            x++;
            break;
        case L'\n':
            x = 0;
            y++;
            break;
        case L'\t':
            for (int j = 0; j < 4; j++)
            {
                WriteToVideoMemory(L' ', x, y);
                x++;
            }
            break;
        default:
            WriteToVideoMemory(str[i], x, y);
            ;
            x++;
            break;
        }

        if (x >= 80)
        {
            x = 0;
            y++;
        }

        if (y >= 25)
        {
            for (y = 0; y < 25; y++)
                for (x = 0; x < 80; x++)
                    VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | 0;

            x = 0;
            y = 0;
        }
    }
}

void printHexf(uint8_t key)
{
    wchar_t *foo = L"00";
    wchar_t *hex = L"0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0x0F];
    foo[1] = hex[key & 0x0F];
    printf(foo);
}

class KeyEventListener : public KeyboardEventHandler
{
public:
    virtual void OnKeyUp(wchar_t *keydata, uint8_t key)
    {
    }

    virtual void OnKeyDown(wchar_t *keydata, uint8_t key)
    {
        printf(keydata);
    }
};

class MouseEventListener : public MouseEventHandler
{
    int8_t x, y;

public:
    virtual void OnActivate()
    {
        static uint16_t *VideoMemory = (uint16_t *)0xb8000;

        VideoMemory[80 * 12 + 40] = ((VideoMemory[80 * 12 + 40] & 0xF000) << 4) | ((VideoMemory[80 * 12 + 40] & 0x0F00) >> 4) | ((VideoMemory[80 * 12 + 40] & 0x00FF) >> 4);
    }

    virtual void OnMouseDown(uint8_t button)
    {
        static uint16_t *VideoMemory = (uint16_t *)0xb8000;
        VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0x0F00) << 4 | (VideoMemory[80 * y + x] & 0xF000) >> 4 | (VideoMemory[80 * y + x] & 0x00FF);
    }
    virtual void OnMouseUp(uint8_t button)
    {
    }

    virtual void OnMouseMove(int8_t xoffset, int8_t yoffset)
    {
        static uint16_t *VideoMemory = (uint16_t *)0xb8000;
        VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0x0F00) << 4 | (VideoMemory[80 * y + x] & 0xF000) >> 4 | (VideoMemory[80 * y + x] & 0x00FF);

        x += xoffset;
        if (x >= 80)
            x = 79;
        if (x < 0)
            x = 0;
        y += yoffset;
        if (y >= 25)
            y = 24;
        if (y < 0)
            y = 0;

        VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0x0F00) << 4 | (VideoMemory[80 * y + x] & 0xF000) >> 4 | (VideoMemory[80 * y + x] & 0x00FF);
    }
};

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for (constructor *i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void kernelMain(void *multiboot_structure, uint32_t magicnumber)
{
    GlobalDescriptorTable gdt;
    InterruptManager interrupts(&gdt);

    printf(L"Initializing Hardware, Stage 1\n");

    DriverManager drvmgr;

    KeyEventListener klistener;

    MouseEventListener mlistener;

    KeyboardDriver keyboard(&interrupts, &klistener);
    drvmgr.AddDriver(&keyboard);
    MouseDriver mouse(&interrupts, &mlistener);
    drvmgr.AddDriver(&mouse);

    PeripheralComponentInterconnectController pciController;
    pciController.SelectDrivers(&drvmgr, &interrupts);

    VideoGraphicsArray vga;
    printf(L"Initializing Hardware, Stage 2\n");

    drvmgr.ActivateAll();
    printf(L"Initializing Hardware, Stage 3\n");
    interrupts.Activate();

    vga.SetMode(320, 200, 8);

    for (int32_t y = 0; y < 100; y++)
    {
        for (int32_t x = 0; x < 160; x++)
        {
            vga.PutPixel(x, y, (uint8_t) RED);
        }

        for (int32_t x = 160; x < 320; x++)
        {
            vga.PutPixel(x, y, BRIGHT_CYAN);
        }
        
    }

    for (int32_t y = 100; y < 200; y++)
    {
        for (int32_t x = 0; x < 160; x++)
        {
            vga.PutPixel(x, y, (uint8_t) GREEN);
        }

        for (int32_t x = 160; x < 320; x++)
        {
            vga.PutPixel(x, y, (uint8_t) BLUE);
        }
    }
    
    

    while (1)
        ;
}
