
#ifndef __KITEOS__GUI__DESKTOP_H
#define __KITEOS__GUI__DESKTOP_H

#include <gui/widget.h>
#include <drivers/mouse.h>
#include <common/graphicscontext.h>
#include <drivers/vga.h>

namespace kiteos
{
    namespace gui
    {

        class Desktop : public CompositeWidget, public kiteos::drivers::MouseEventHandler
        {
        protected:
            common::int32_t MouseX, MouseY; 

        public:
            Desktop(Widget *parent, common::int32_t x, common::int32_t y, common::int32_t w, common::int32_t h, common::uint8_t color);
            ~Desktop();

            void Draw(common::GraphicsContext *gc); 

            void DrawMouse(common::GraphicsContext *gc);

            void OnMouseDown(common::uint8_t button);
            void OnMouseUp(common::uint8_t button);
            void OnMouseMove(int x, int y);
        };

    } // namespace gui

} // namespace kiteos

#endif