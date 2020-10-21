#ifndef __KITEOS__GUI__WIDGET
#define __KITEOS__GUI__WIDGET

#include <common/types.h>
#include <common/graphicscontext.h>

#include <drivers/keyboard.h>
#include <drivers/mouse.h>

namespace kiteos
{
    namespace gui
    {
        class Widget : public kiteos::drivers::KeyboardEventHandler
        {
        protected:
            Widget *parent;
            common::int32_t x, y, w, h;
            common::int32_t dx, dy;
            common::uint8_t color;

            bool Focusable;

        public:
            bool isMouseOver;
            Widget(Widget *parent, common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h, common::uint8_t color);
            ~Widget();

            virtual void GetFocus(Widget *widget);
            virtual void ModelToScreen(common::int32_t &x, common::int32_t &y);
            virtual bool ContainsCoordinate(common::int32_t x, common::int32_t y);

            virtual void Draw(common::GraphicsContext *gc);
        
            virtual void OnMouseDown(common::int32_t x, common::int32_t y, common::uint8_t button);
            virtual void OnMouseUp(common::int32_t x, common::int32_t y, common::uint8_t button);
            virtual void OnMouseMove(common::int32_t oldx, common::int32_t oldy, common::int32_t newx, common::int32_t newy);
            virtual void OnMouseOver(common::int32_t x, common::int32_t y);
            virtual void OnMouseOut(common::int32_t x, common::int32_t y);
        };

        class CompositeWidget : public Widget
        {
        protected:
            Widget *children[500];
            int numChildren;
            Widget *focusedChild;
        public:

            CompositeWidget(Widget *parent, common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h, common::uint8_t color);
            ~CompositeWidget();

            virtual void GetFocus(Widget *widget);
            virtual bool AddChild(Widget *widget);


            virtual void DrawChildren(common::GraphicsContext *gc);

            virtual void Draw(common::GraphicsContext *gc);
            virtual void OnMouseDown(common::int32_t x, common::int32_t y, common::uint8_t button);
            virtual void OnMouseUp(common::int32_t x, common::int32_t y, common::uint8_t button);
            virtual void OnMouseMove(common::int32_t oldx, common::int32_t oldy, common::int32_t newx, common::int32_t newy);
            virtual void OnMouseOver(common::int32_t x, common::int32_t y);
            virtual void OnMouseOut(common::int32_t x, common::int32_t y);

            virtual void OnKeyDown(wchar_t *keychar, common::uint8_t keycode);
            virtual void OnKeyUp(wchar_t *keychar, common::uint8_t keycode);
        };
    } // namespace gui

} // namespace kiteos

#endif