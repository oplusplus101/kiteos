#include <drivers/keyboard.h>

using namespace kiteos;
using namespace kiteos::common;
using namespace kiteos::drivers;
using namespace kiteos::hardwarecommunication;

void printf(wchar_t *);
void printHexf(uint8_t);

KeyboardEventHandler::KeyboardEventHandler()
{
}

void KeyboardEventHandler::OnKeyDown(wchar_t *keydata, uint8_t keyid)
{
}

void KeyboardEventHandler::OnKeyUp(wchar_t *keydata, uint8_t keyid)
{
}

KeyboardDriver::KeyboardDriver(InterruptManager *interruptManager, KeyboardEventHandler *handler)
    : InterruptHandler(0x21, interruptManager),
      dataport(0x60),
      commandport(0x64)
{
    this->handler = handler;
}

KeyboardDriver::~KeyboardDriver()
{
}

void KeyboardDriver::Activate()
{
    if (handler != 0)
    {
        printf(L"KH IS NOT NULL\n");
    }
    else
    {
        printf(L"KH NOT NULL\n");
    }
    while (commandport.Read() & 0x1)
        dataport.Read();
    commandport.Write(0xae); // activate interrupts
    commandport.Write(0x20); // command 0x20 = read controller command byte
    uint8_t status = (dataport.Read() | 1) & ~0x10;
    commandport.Write(0x60); // command 0x60 = set controller command byte
    dataport.Write(status);
    dataport.Write(0xf4);
    printf(L"YES\n");
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();

    if (handler == 0) {
        printf(L"NONONONONONONONONONONONONONONONNOO");
        return esp;
    }

    static bool Shift = false;

    switch (key)
    {
    case 0x10:
        if (Shift)
            handler->OnKeyDown(L"Q", key);
        else
            handler->OnKeyDown(L"q", key);
        break;
    case 0x11:
        if (Shift)
            handler->OnKeyDown(L"W", key);
        else
            handler->OnKeyDown(L"w", key);
        break;
    case 0x12:
        if (Shift)
            handler->OnKeyDown(L"E", key);
        else
            handler->OnKeyDown(L"e", key);
        break;
    case 0x13:
        if (Shift)
            handler->OnKeyDown(L"R", key);
        else
            handler->OnKeyDown(L"r", key);
        break;
    case 0x14:
        if (Shift)
            handler->OnKeyDown(L"T", key);
        else
            handler->OnKeyDown(L"t", key);
        break;
    case 0x15:
        if (Shift)
            handler->OnKeyDown(L"Z", key);
        else
            handler->OnKeyDown(L"z", key);
        break;
    case 0x16:
        if (Shift)
            handler->OnKeyDown(L"U", key);
        else
            handler->OnKeyDown(L"u", key);
        break;
    case 0x17:
        if (Shift)
            handler->OnKeyDown(L"I", key);
        else
            handler->OnKeyDown(L"i", key);
        break;
    case 0x18:
        if (Shift)
            handler->OnKeyDown(L"O", key);
        else
            handler->OnKeyDown(L"o", key);
        break;
    case 0x19:
        if (Shift)
            handler->OnKeyDown(L"P", key);
        else
            handler->OnKeyDown(L"p", key);
        break;
    //
    //
    case 0x1A:
        handler->OnKeyDown(L"ü", key);
        break;
    case 0x1E:
        if (Shift)
            handler->OnKeyDown(L"A", key);
        else
            handler->OnKeyDown(L"a", key);
        break;
    case 0x1F:
        if (Shift)
            handler->OnKeyDown(L"S", key);
        else
            handler->OnKeyDown(L"s", key);
        break;
    case 0x20:
        if (Shift)
            handler->OnKeyDown(L"D", key);
        else
            handler->OnKeyDown(L"d", key);
        break;
    case 0x21:
        if (Shift)
            handler->OnKeyDown(L"F", key);
        else
            handler->OnKeyDown(L"f", key);
        break;
    case 0x22:
        if (Shift)
            handler->OnKeyDown(L"G", key);
        else
            handler->OnKeyDown(L"g", key);
        break;
    case 0x23:
        if (Shift)
            handler->OnKeyDown(L"H", key);
        else
            handler->OnKeyDown(L"h", key);
        break;
    case 0x24:
        if (Shift)
            handler->OnKeyDown(L"J", key);
        handler->OnKeyDown(L"j", key);
        break;
    case 0x25:
        if (Shift)
            handler->OnKeyDown(L"K", key);
        else
            handler->OnKeyDown(L"k", key);
        break;
    case 0x26:
        if (Shift)
            handler->OnKeyDown(L"L", key);
        else
            handler->OnKeyDown(L"l", key);
        break;
    case 0x27:
        handler->OnKeyDown(L"ö", key);
        break;
    case 0x28:
        handler->OnKeyDown(L"ä", key);
        break;
    case 0x2C:
        if (Shift)
            handler->OnKeyDown(L"Y", key);
        else
            handler->OnKeyDown(L"y", key);
        break;
    case 0x2D:
        if (Shift)
            handler->OnKeyDown(L"X", key);
        else
            handler->OnKeyDown(L"x", key);
        break;
    case 0x2E:
        if (Shift)
            handler->OnKeyDown(L"C", key);
        else
            handler->OnKeyDown(L"c", key);
        break;
    case 0x2F:
        if (Shift)
            handler->OnKeyDown(L"V", key);
        else
            handler->OnKeyDown(L"v", key);
        break;
    case 0x30:
        if (Shift)
            handler->OnKeyDown(L"B", key);
        else
            handler->OnKeyDown(L"b", key);
        break;
    case 0x31:
        if (Shift)
            handler->OnKeyDown(L"N", key);
        else
            handler->OnKeyDown(L"n", key);
        break;
    case 0x32:
        if (Shift)
            handler->OnKeyDown(L"M", key);
        else
            handler->OnKeyDown(L"m", key);
        break;

    // SPETIAL
    case 0x39:
        handler->OnKeyDown(L" ", key);
        break;
    case 0x1C:
        handler->OnKeyDown(L"\n", key);
        break;
    case 0x0E:
        handler->OnKeyDown(L"\a", key);
        break;

    case 0x2A:
    case 0x36:
        Shift = true;
        break;
    case 0xAA:
    case 0xB6:
        Shift = false;
        break;

    case 0x33:
        if (Shift)
            handler->OnKeyDown(L";", key);
        else
            handler->OnKeyDown(L",", key);
        break;

    case 0x34:
        if (Shift)
            handler->OnKeyDown(L":", key);
        else
            handler->OnKeyDown(L".", key);
        break;

    case 0x35:
        if (Shift)
            handler->OnKeyDown(L"_", key);
        else
            handler->OnKeyDown(L"-", key);
        break;

    case 0x56:
        if (Shift)
            handler->OnKeyDown(L">", key);
        else
            handler->OnKeyDown(L"<", key);
        break;

        // NUMBERS

    case 0x02:
        if (Shift)
            handler->OnKeyDown(L"+", key);
        else
            handler->OnKeyDown(L"1", key);
        break;

    case 0x03:
        if (Shift)
            handler->OnKeyDown(L"\"", key);
        else
            handler->OnKeyDown(L"2", key);
        break;

    case 0x04:
        if (Shift)
            handler->OnKeyDown(L"*", key);
        else
            handler->OnKeyDown(L"3", key);
        break;

    case 0x05:
        if (Shift)
            handler->OnKeyDown(L"ç", key);
        else
            handler->OnKeyDown(L"4", key);
        break;

    case 0x06:
        if (Shift)
            handler->OnKeyDown(L"%", key);
        else
            handler->OnKeyDown(L"5", key);
        break;

    case 0x07:
        if (Shift)
            handler->OnKeyDown(L"&", key);
        else
            handler->OnKeyDown(L"6", key);
        break;

    case 0x08:
        if (Shift)
            handler->OnKeyDown(L"/", key);
        else
            handler->OnKeyDown(L"7", key);
        break;

    case 0x09:
        if (Shift)
            handler->OnKeyDown(L"(", key);
        else
            handler->OnKeyDown(L"8", key);
        break;

    case 0x0A:
        if (Shift)
            handler->OnKeyDown(L")", key);
        else
            handler->OnKeyDown(L"9", key);
        break;

    case 0x0B:
        if (Shift)
            handler->OnKeyDown(L"=", key);
        else
            handler->OnKeyDown(L"0", key);
        break;

    // TO IGNORE
    case 0x45:
    case 0xC5:
    case 0xFA:
        break;

    default:

        break;
    }

    return esp;
}
