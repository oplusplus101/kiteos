
#include <gui/window.h>

using namespace kiteos::common;
using namespace kiteos::gui;
using namespace kiteos::drivers;
using namespace kiteos::common;


Window::Window(Widget *parent, int32_t x, int32_t y, int32_t w, int32_t h, uint8_t color)
    : CompositeWidget(parent, x, y, w, h, color),
      Draging(false)
{
}

Window::~Window()
{

}

void Window::Draw(GraphicsContext *gc)
{

    if (dx < 0 || dx > 0 || dy < 0 || dy > 0)
        gc->FillRect(x - 4, y - 4, w + 8, h + 8, CYAN);

    gc->FillRect(x, y + 6, w, h - 6, BRIGHT_GRAY);
    gc->FillRect(x, y, w, 6, DARK_GRAY);
}

void Window::OnMouseDown(int32_t x, int32_t y, uint8_t button)
{
    CompositeWidget::OnMouseDown(x, y, button);
    if (this->x <= x || x <= w || this->y <= y || y <= this->y + 6)
        Draging = button == 1;
}

void Window::OnMouseUp(int32_t x, int32_t y, uint8_t button)
{
    CompositeWidget::OnMouseUp(x, y, button);
    Draging = false;
}

void Window::OnMouseMove(int32_t oldx, int32_t oldy, int32_t newx, int32_t newy)
{
    this->dx = newx - oldx;
    this->dy = newy - oldy;
    CompositeWidget::OnMouseMove(oldx, oldy, newx, newy);
    if (Draging)
    {
        this->x += dx;
        this->y += dy;
    }

}
