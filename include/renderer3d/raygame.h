
#ifndef __KITEOS__RENDERER3D__RAYGAME_H
#define __KITEOS__RENDERER3D__RAYGAME_H

#include <drivers/vga.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <types.h>
#include <common/graphicscontext.h>
#include <common/math.h>


namespace kiteos
{
    namespace renderer3d
    {
        class RayGame : public drivers::MouseEventHandler, public drivers::KeyboardEventHandler
        {
        private:
            
            char *map = 
            "################"
            "#..............#"
            "#..............#"
            "#..............#"
            "#..............#"
            "#..............#"
            "#..........#...#"
            "#.......#......#"
            "#..............#"
            "#..............#"
            "#..............#"
            "#..............#"
            "#..............#"
            "#..............#"
            "#..............#"
            "################";
            common::uint16_t mapWidth = 16, mapHeight = 16;

            float playerX, playerY, playerA, fov = 3.14159 / 4.0f, depth = 16;

        public:
            RayGame();
            ~RayGame();

        private:
            void Update();
        public:

            void Render(common::GraphicsContext g);
        };
    } // namespace renderer3d

} // namespace kiteos

#endif