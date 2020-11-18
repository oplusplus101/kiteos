#include <drivers/keyboard.h>

using namespace kiteos;
using namespace kiteos::common;
using namespace kiteos::drivers;
using namespace kiteos::hardwarecommunication;

void printf(char *);
void printHexf(uint8_t);

KeyboardEventHandler::KeyboardEventHandler()
{
}

void KeyboardEventHandler::OnKeyDown(char *keydata, uint8_t keyid)
{
}

void KeyboardEventHandler::OnKeyUp(char *keydata, uint8_t keyid)
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
    while (commandport.Read() & 0x1)
        dataport.Read();
    commandport.Write(0xae); // activate interrupts
    commandport.Write(0x20); // command 0x20 = read controller command byte
    uint8_t status = (dataport.Read() | 1) & ~0x10;
    commandport.Write(0x60); // command 0x60 = set controller command byte
    dataport.Write(status);
    dataport.Write(0xf4);
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();

    if (handler == 0) {
        return esp;
    }

    static bool Shift = false;

    switch (key)
    {
    case 0x10:
        if (Shift)
            handler->OnKeyDown("Q", key);
        else
            handler->OnKeyDown("q", key);
        break;
    case 0x11:
        if (Shift)
            handler->OnKeyDown("W", key);
        else
            handler->OnKeyDown("w", key);
        break;
    case 0x12:
        if (Shift)
            handler->OnKeyDown("E", key);
        else
            handler->OnKeyDown("e", key);
        break;
    case 0x13:
        if (Shift)
            handler->OnKeyDown("R", key);
        else
            handler->OnKeyDown("r", key);
        break;
    case 0x14:
        if (Shift)
            handler->OnKeyDown("T", key);
        else
            handler->OnKeyDown("t", key);
        break;
    case 0x15:
        if (Shift)
            handler->OnKeyDown("Z", key);
        else
            handler->OnKeyDown("z", key);
        break;
    case 0x16:
        if (Shift)
            handler->OnKeyDown("U", key);
        else
            handler->OnKeyDown("u", key);
        break;
    case 0x17:
        if (Shift)
            handler->OnKeyDown("I", key);
        else
            handler->OnKeyDown("i", key);
        break;
    case 0x18:
        if (Shift)
            handler->OnKeyDown("O", key);
        else
            handler->OnKeyDown("o", key);
        break;
    case 0x19:
        if (Shift)
            handler->OnKeyDown("P", key);
        else
            handler->OnKeyDown("p", key);
        break;
    //
    //
    case 0x1A:
        handler->OnKeyDown("ü", key);
        break;
    case 0x1E:
        if (Shift)
            handler->OnKeyDown("A", key);
        else
            handler->OnKeyDown("a", key);
        break;
    case 0x1F:
        if (Shift)
            handler->OnKeyDown("S", key);
        else
            handler->OnKeyDown("s", key);
        break;
    case 0x20:
        if (Shift)
            handler->OnKeyDown("D", key);
        else
            handler->OnKeyDown("d", key);
        break;
    case 0x21:
        if (Shift)
            handler->OnKeyDown("F", key);
        else
            handler->OnKeyDown("f", key);
        break;
    case 0x22:
        if (Shift)
            handler->OnKeyDown("G", key);
        else
            handler->OnKeyDown("g", key);
        break;
    case 0x23:
        if (Shift)
            handler->OnKeyDown("H", key);
        else
            handler->OnKeyDown("h", key);
        break;
    case 0x24:
        if (Shift)
            handler->OnKeyDown("J", key);
        handler->OnKeyDown("j", key);
        break;
    case 0x25:
        if (Shift)
            handler->OnKeyDown("K", key);
        else
            handler->OnKeyDown("k", key);
        break;
    case 0x26:
        if (Shift)
            handler->OnKeyDown("", key);
        else
            handler->OnKeyDown("l", key);
        break;
    case 0x27:
        handler->OnKeyDown("ö", key);
        break;
    case 0x28:
        handler->OnKeyDown("ä", key);
        break;
    case 0x2C:
        if (Shift)
            handler->OnKeyDown("Y", key);
        else
            handler->OnKeyDown("y", key);
        break;
    case 0x2D:
        if (Shift)
            handler->OnKeyDown("X", key);
        else
            handler->OnKeyDown("x", key);
        break;
    case 0x2E:
        if (Shift)
            handler->OnKeyDown("C", key);
        else
            handler->OnKeyDown("c", key);
        break;
    case 0x2F:
        if (Shift)
            handler->OnKeyDown("V", key);
        else
            handler->OnKeyDown("v", key);
        break;
    case 0x30:
        if (Shift)
            handler->OnKeyDown("B", key);
        else
            handler->OnKeyDown("b", key);
        break;
    case 0x31:
        if (Shift)
            handler->OnKeyDown("N", key);
        else
            handler->OnKeyDown("n", key);
        break;
    case 0x32:
        if (Shift)
            handler->OnKeyDown("M", key);
        else
            handler->OnKeyDown("m", key);
        break;

    // SPETIAL
    case 0x39:
        handler->OnKeyDown(" ", key);
        break;
    case 0x1C:
        handler->OnKeyDown("\n", key);
        break;
    case 0x0E:
        handler->OnKeyDown("\a", key);
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
            handler->OnKeyDown(";", key);
        else
            handler->OnKeyDown(",", key);
        break;

    case 0x34:
        if (Shift)
            handler->OnKeyDown(":", key);
        else
            handler->OnKeyDown(".", key);
        break;

    case 0x35:
        if (Shift)
            handler->OnKeyDown("_", key);
        else
            handler->OnKeyDown("-", key);
        break;

    case 0x56:
        if (Shift)
            handler->OnKeyDown(">", key);
        else
            handler->OnKeyDown("<", key);
        break;

        // NUMBERS

    case 0x02:
        if (Shift)
            handler->OnKeyDown("+", key);
        else
            handler->OnKeyDown("1", key);
        break;

    case 0x03:
        if (Shift)
            handler->OnKeyDown("\"", key);
        else
            handler->OnKeyDown("2", key);
        break;

    case 0x04:
        if (Shift)
            handler->OnKeyDown("*", key);
        else
            handler->OnKeyDown("3", key);
        break;

    case 0x05:
        if (Shift)
            handler->OnKeyDown("ç", key);
        else
            handler->OnKeyDown("4", key);
        break;

    case 0x06:
        if (Shift)
            handler->OnKeyDown("%", key);
        else
            handler->OnKeyDown("5", key);
        break;

    case 0x07:
        if (Shift)
            handler->OnKeyDown("&", key);
        else
            handler->OnKeyDown("6", key);
        break;

    case 0x08:
        if (Shift)
            handler->OnKeyDown("/", key);
        else
            handler->OnKeyDown("7", key);
        break;

    case 0x09:
        if (Shift)
            handler->OnKeyDown("(", key);
        else
            handler->OnKeyDown("8", key);
        break;

    case 0x0A:
        if (Shift)
            handler->OnKeyDown(")", key);
        else
            handler->OnKeyDown("9", key);
        break;

    case 0x0B:
        if (Shift)
            handler->OnKeyDown("=", key);
        else
            handler->OnKeyDown("0", key);
        break;

    // TO IGNORE
    case 0x45:
    case 0xC5:
    case 0xFA:
        break;

    default:
        // printf("KEY 0x");
        // printHexf(key);
        break;
    }

    return esp;
}
