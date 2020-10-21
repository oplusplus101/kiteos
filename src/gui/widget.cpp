#include <gui/widget.h>

using namespace kiteos::gui;
using namespace kiteos::common;

Widget::Widget(Widget *parent, int32_t x, int32_t y, int32_t w, int32_t h, uint8_t color)
    : parent(parent),
      x(x), y(y), w(w), h(h),
      color(color),
      Focusable(true)
{
}

Widget::~Widget()
{
}

void Widget::GetFocus(Widget *widget)
{
    if (parent != 0)
        parent->GetFocus(widget);
}

void Widget::ModelToScreen(int32_t &x, int32_t &y)
{
    if (parent != 0)
        parent->ModelToScreen(x, y);

    x += this->x;
    y += this->y;
}

bool Widget::ContainsCoordinate(int32_t x, int32_t y)
{
    return this->x <= x && x < this->x + this->w && this->y <= y && y < this->y + this->h;
}

void Widget::Draw(GraphicsContext *gc)
{
    int X = 0, Y = 0;
    ModelToScreen(X, Y);
    gc->FillRect(X, Y, w, h, color);
}

void Widget::OnMouseDown(int32_t x, int32_t y, uint8_t button)
{
    if (Focusable)
        GetFocus(this);
}

void Widget::OnMouseUp(int32_t x, int32_t y, uint8_t button)
{
}

void Widget::OnMouseMove(int32_t oldx, int32_t oldy, int32_t newx, int32_t newy)
{
}

void Widget::OnMouseOver(int32_t x, int32_t y)
{
}

void Widget::OnMouseOut(int32_t x, int32_t y)
{
}

CompositeWidget::CompositeWidget(Widget *parent, int32_t x, int32_t y, int32_t w, int32_t h, uint8_t color)
    : Widget(parent, x, y, w, h, color),
      focusedChild(0),
      numChildren(0)
{
}

CompositeWidget::~CompositeWidget()
{
}

void CompositeWidget::GetFocus(Widget *widget)
{
    this->focusedChild = widget;
    if (parent != 0)
        parent->GetFocus(this);
}

bool CompositeWidget::AddChild(Widget *child)
{
    if(numChildren >= 500)
        return false;
    children[numChildren++] = child;
    return true;
}

void CompositeWidget::Draw(GraphicsContext *gc)
{
    Widget::Draw(gc);
    DrawChildren(gc);
}

void CompositeWidget::DrawChildren(GraphicsContext *gc)
{
    for (int i = numChildren - 1; i >= 0; i--)
        children[i]->Draw(gc);
}


void CompositeWidget::OnMouseDown(int32_t x, int32_t y, uint8_t button)
{
    for (uint16_t i = 0; i < numChildren; i++)
    {
        if (children[i]->ContainsCoordinate(x - this->x, y - this->y))
        {
            children[i]->OnMouseDown(x - this->x, y - this->y, button);
            break;
        }
    }
}

void CompositeWidget::OnMouseUp(int32_t x, int32_t y, uint8_t button)
{
    for (uint16_t i = 0; i < numChildren; i++)
    {
        if (children[i]->ContainsCoordinate(x - this->x, y - this->y))
        {
            children[i]->OnMouseUp(x - this->x, y - this->y, button);
            break;
        }
    }
}

void CompositeWidget::OnMouseMove(int32_t oldx, int32_t oldy, int32_t newx, int32_t newy)
{
    int firstchild = -1;

    for (uint16_t i = 0; i < numChildren; i++)
    {

        if (children[i]->ContainsCoordinate(oldx - this->x, oldy - this->y))
        {
            children[i]->OnMouseMove(oldx, oldy, newx, newy);
            firstchild = i;
            break;
        }
    }

    for (uint16_t i = 0; i < numChildren; i++)
    {

        if (children[i]->ContainsCoordinate(oldx - this->x, oldy - this->y))
        {
            if (firstchild != i)
                children[i]->OnMouseMove(oldx, oldy, newx, newy);
            break;
        }
    }
}

void CompositeWidget::OnMouseOver(int32_t x, int32_t y)
{
    for (uint16_t i = 0; i < numChildren; i++)
    {
        if (children[i]->ContainsCoordinate(x - this->x, y - this->y))
        {
            if (!children[i]->isMouseOver)
                children[i]->OnMouseOver(x, y);
            children[i]->isMouseOver = true;
            break;
        }
    }
}

void CompositeWidget::OnMouseOut(int32_t x, int32_t y)
{
    for (uint16_t i = 0; i < numChildren; i++)
    {

        if (children[i]->isMouseOver && !children[i]->ContainsCoordinate(x - this->x, y - this->y))
            children[i]->OnMouseOut(x, y);
        children[i]->isMouseOver = false;
        break;
    }
}

void CompositeWidget::OnKeyDown(wchar_t *keychar, uint8_t keycode)
{
    if (focusedChild != 0)
        focusedChild->OnKeyDown(keychar, keycode);
}

void CompositeWidget::OnKeyUp(wchar_t *keychar, uint8_t keycode)
{
    if (focusedChild != 0)
        focusedChild->OnKeyDown(keychar, keycode);
}
