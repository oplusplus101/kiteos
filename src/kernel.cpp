#include <gdt.h>
#include <common/types.h>
#include <hardwarecommunication/interrupts.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/driver.h>
#include <hardwarecommunication/pci.h>
#include <common/osutil.h>
#include <drivers/vga.h>
#include <gui/widget.h>
#include <gui/desktop.h>
#include <gui/window.h>
#include <drivers/dbrenderer.h>
#include <multitasking.h>
#include <memorymanagement.h>

/*
\204 => ä
\224 => ö
\201 => ü
*/

using namespace kiteos;
using namespace kiteos::common;
using namespace kiteos::drivers;
using namespace kiteos::hardwarecommunication;
using namespace kiteos::gui;

void printf(wchar_t *str)
{
    static uint16_t *VideoMemory = (uint16_t *)0xb8000;

    static uint8_t x = 0, y = 0;

    for (int i = 0; str[i] != '\0'; ++i)
    {
        switch (str[i])
        {
        case '\n':
            x = 0;
            y++;
            break;
        default:
            VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | str[i];
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
                    VideoMemory[80 * y + x] = (VideoMemory[80 * y + x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

int strlen(wchar_t s[]) {
   int c = 0;
   while (s[c] != '\0')
      c++;

   return c;
}

wchar_t *strrev(wchar_t *str){
    wchar_t c, *front, *back;

    if(!str || !*str)
        return str;
    for(front=str,back=str+strlen(str)-1;front < back;front++,back--){
        c=*front;*front=*back;*back=c;
    }
    return str;
}

char *printDecf(int v, int radix_base){
    static char table[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    wchar_t buff[33];
    wchar_t *p=buff;
    unsigned int n = (v < 0 && radix_base == 10)? -v : (unsigned int) v;
    while(n>=radix_base){
        *p++=table[n%radix_base];
        n/=radix_base;
    }
    *p++=table[n];
    if(v < 0 && radix_base == 10) *p++='-';
    *p='\0';
    printf(strrev(buff));
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
        printf(L"HAHA");
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

void TaskA()
{
}

void TaskB()
{
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for (constructor *i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

// #define DESKTOP

extern "C" void kernelMain(void *multiboot_structure, uint32_t magicnumber)
{
    GlobalDescriptorTable gdt;

    TaskManager taskManager;
    // Task task1(&gdt, TaskA);
    // Task task2(&gdt, TaskB);

    // taskManager.AddTask(&task1);
    // taskManager.AddTask(&task2);

    InterruptManager interrupts(0x20, &gdt, &taskManager);

    uint32_t *memuper = (uint32_t *)(((size_t)multiboot_structure) + 8);
    size_t heap = FromMegaBytes(10);
    MemoryManager memoryManager(heap, (*memuper) * 1024 - heap - 10 * 1024);

    printf(L"Heap: ");
    printDecf(heap, 10);

    void *allocated = memoryManager.malloc(1024);

    printf(L"\nAllocated: ");
    printDecf((uint32_t)allocated, 10); 
    printf(L"\n");

    printf(L"Initializing Hardware, Stage 1\n");
#ifdef DESKTOP
    Desktop desktop(0, 0, 0, 320, 200, CYAN);
#endif
    DriverManager drvmgr;

#ifdef DESKTOP
    KeyboardDriver keyboard(&interrupts, &desktop);
    drvmgr.AddDriver(&keyboard);
    MouseDriver mouse(&interrupts, &desktop);
    drvmgr.AddDriver(&mouse);
#else
    KeyEventListener kl;
    MouseEventListener ml;
    KeyboardDriver keyboard(&interrupts, &kl);
    drvmgr.AddDriver(&keyboard);
    MouseDriver mouse(&interrupts, &ml);
    drvmgr.AddDriver(&mouse);
#endif

    PeripheralComponentInterconnectController pciController;
    pciController.SelectDrivers(&drvmgr, &interrupts);

#ifdef DESKTOP
    VideoGraphicsArray vga;
#endif
    printf(L"Initializing Hardware, Stage 2\n");

    drvmgr.ActivateAll();
    printf(L"Initializing Hardware, Stage 3\n");
#ifdef DESKTOP
    vga.SetMode(320, 200, 8);
#endif
    interrupts.Activate();

#ifdef DESKTOP

    Window win1(&desktop, 10, 10, 20, 20, RED);
    desktop.AddChild(&win1);
    Window win2(&desktop, 40, 15, 30, 30, RED);
    desktop.AddChild(&win2);

    desktop.Draw(&vga);
#endif

    while (1)
    {
#ifdef DESKTOP
        vga.DrawText("Hello, world!", 0, 16, WHITE);
        desktop.DrawChildren(&vga);
        desktop.DrawMouse(&vga);
#endif
    }
}
