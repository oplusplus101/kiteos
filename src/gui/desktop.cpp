
#include <gui/desktop.h>

using namespace kiteos::common;
using namespace kiteos::gui;
using namespace kiteos::drivers;

void printf(wchar_t *str);

Desktop::Desktop(Widget *parent, int32_t x, int32_t y, int32_t w, int32_t h, uint8_t color)
    : CompositeWidget(parent, x, y, w, h, color),
      MouseEventHandler()
{
    MouseX = w / 2;
    MouseY = h / 2;
}

Desktop::~Desktop()
{

}


void Desktop::Draw(GraphicsContext *gc)
{
    CompositeWidget::Draw(gc);   
}

void Desktop::DrawMouse(GraphicsContext *gc)
{
    gc->FillRect(MouseX - 6, MouseY - 6, 12, 12, CYAN);
    for (int i = 0; i < 4; i++)
    {
        gc->PutPixel(MouseX+i, MouseY, RED);
        gc->PutPixel(MouseX-i, MouseY, RED);
        gc->PutPixel(MouseX, MouseY+i, RED);
        gc->PutPixel(MouseX, MouseY-i, RED);
    }
}


void Desktop::OnMouseDown(uint8_t button)
{
    CompositeWidget::OnMouseDown(MouseX, MouseY, button);
}

void Desktop::OnMouseUp(uint8_t button)
{
    CompositeWidget::OnMouseUp(MouseX, MouseY, button);
}

void Desktop::OnMouseMove(int x, int y)
{
    x /= 4;
    y /= 4;

    int32_t newMouseX = MouseX + x;
    if (newMouseX < 0)
        newMouseX = 0;
    if (newMouseX >= w)
        newMouseX = w - 1;
    
    int32_t newMouseY = MouseY + y;
    if (newMouseY < 0)
        newMouseY = 0;
    if (newMouseY >= h)
        newMouseY = h - 1;

    CompositeWidget::OnMouseMove(MouseX, MouseY, newMouseX, newMouseY);

    MouseX = newMouseX;
    MouseY = newMouseY;
}
