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
#include <common/math.h>
#include <drivers/pcspeaker.h>

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

int printx, printy;

void printf(char *str)
{
    static uint16_t *VideoMemory = (uint16_t *)0xb8000;

    for (int i = 0; str[i] != '\0'; ++i)
    {
        switch (str[i])
        {
        case '\n':
            printx = 0;
            printy++;
            break;
        case '\a':
            VideoMemory[80 * printy + printx] = (VideoMemory[80 * printy + printx] & 0xFF00) | ' ';
            printx--;
            break;
        default:
            VideoMemory[80 * printy + printx] = (VideoMemory[80 * printy + printx] & 0xFF00) | str[i];
            printx++;
            break;
        }

        if (printx >= 80)
        {
            printx = 0;
            printy++;
        }

        if (printy >= 25)
        {
            for (printy = 0; printy < 25; printy++)
                for (printx = 0; printx < 80; printx++)
                    VideoMemory[80 * printy + printx] = (VideoMemory[80 * printy + printx] & 0xFF00) | ' ';
            printx = 0;
            printy = 0;
        }
    }
}

void memset(char *buf, char v, int len)
{
    while (buf && len > 0)
    {
        buf = (char *)v;
        buf++;
        len--;
    }
}

int strlen(char s[])
{
    int c = 0;
    while (s[c] != L'\0')
        c++;

    return c;
}

char *strcpy(char *dest, char *src, int length)
{
    for (int i = 0; i < length; i++)
    {
        dest[i] = src[i];
    }
}

char *strrev(char *str)
{
    char c, *front, *back;

    if (!str || !*str)
        return str;
    for (front = str, back = str + strlen(str) - 1; front < back; front++, back--)
    {
        c = *front;
        *front = *back;
        *back = c;
    }
    return str;
}

bool strcmp(char *x, char *y)
{
    int flag = 0;

    // Iterate a loop till the end
    // of both the strings
    while (*x != '\0' || *y != '\0')
    {
        if (*x == *y)
        {
            x++;
            y++;
        }

        // If two characters are not same
        // print the difference and exit
        else if ((*x == '\0' && *y != '\0') || (*x != '\0' && *y == '\0') || *x != *y)
        {
            flag = 1;
            return false;
        }
    }

    // If two strings are exactly same
    if (flag == 0)
    {
        return true;
    }
}

void printDecf(int v, int radix_base)
{
    static char table[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char buff[33];
    char *p = buff;
    unsigned int n = (v < 0 && radix_base == 10) ? -v : (unsigned int)v;
    while (n >= radix_base)
    {
        *p++ = table[n % radix_base];
        n /= radix_base;
    }
    *p++ = table[n];
    if (v < 0 && radix_base == 10)
        *p++ = '-';
    *p = '\0';
    printf(strrev(buff));
}

void printHexf(uint8_t key)
{
    char *foo = "00";
    char *hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0x0F];
    foo[1] = hex[key & 0x0F];
    printf(foo);
}

class KeyEventListener : public KeyboardEventHandler
{
protected:
public:
    static KeyEventListener *active;
    char *currentText;
    bool submit;
    KeyEventListener()
    {
        active = this;
    }
    virtual void OnKeyUp(char *keydata, uint8_t key)
    {
    }

    virtual void OnKeyDown(char *keydata, uint8_t key)
    {
        if (keydata[0] == '\a')
            currentText[strlen(currentText) - 1] = '\0';

        if (keydata[0] == '\n')
        {
            submit = true;
            return;
        }

        printf(keydata);
    }
};

KeyEventListener *KeyEventListener::active;

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

    void *allocated = memoryManager.malloc(1024);

    printf("Initializing Hardware, Stage 1\n");
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
    PCSpeaker pcs;
    drvmgr.AddDriver(&pcs);
    KeyEventListener kl;
    MouseEventListener ml;
    KeyboardDriver keyboard(&interrupts, &kl);
    drvmgr.AddDriver(&keyboard);
    MouseDriver mouse(&interrupts, &ml);
    drvmgr.AddDriver(&mouse);
#endif

    VideoGraphicsArray vga;
    printf("Initializing Hardware, Stage 2\n");

    drvmgr.ActivateAll();
    printf("Initializing Hardware, Stage 3\n");
    // vga.SetMode(320, 200, 8);
    interrupts.Activate();

#ifdef DESKTOP

    Window win1(&desktop, 10, 10, 20, 20, RED);
    desktop.AddChild(&win1);
    Window win2(&desktop, 40, 15, 30, 30, RED);
    desktop.AddChild(&win2);

    desktop.Draw(&vga);
#endif
    // vga.FillRect(0, 0, 320, 200, BLACK);
    while (1)
    {
#ifdef DESKTOP
        vga.DrawText("Hello, world!", 0, 16, WHITE);
        desktop.DrawChildren(&vga);
        desktop.DrawMouse(&vga);
#else
        // pcs.PlaySong("APAPBPBP");
        pcs.Beep();
#endif
    }
}
