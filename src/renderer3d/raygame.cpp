#include <renderer3d/raygame.h>

using namespace kiteos::common;
using namespace kiteos::drivers;
using namespace kiteos::renderer3d;

RayGame::RayGame()
{
}

RayGame::~RayGame()
{

}

void RayGame::Update()
{

}

void RayGame::Render(GraphicsContext g)
{
    Update();
    for (uint32_t x = 0; x < g.width; x++)
    {
        float rayAngle = (playerA - fov / 2.0f) + ((float) x / (float) g.width);
        float distanceToWall = 0;
        
        bool hitWall = false;

        float eyeX = sinf(rayAngle);
        float eyeY = cosf(rayAngle);

        while (!hitWall && distanceToWall < depth)
        {
            distanceToWall += 0.1f;
            int testX = (int)(playerX + eyeX * distanceToWall);
            int testY = (int)(playerY + eyeY * distanceToWall);

            if (testX < 0 || testX > mapWidth || testY < 0 || testY > mapHeight)
            {
                hitWall = true;
                distanceToWall = depth;
            }
            else
            {
                if (map[testY * mapWidth + testX] == '#')
                {
                    hitWall = true;
                }
            }
            
            int ceiling = (float)(g.height / 2.0f) - g.height / ((float)distanceToWall);
            int floor = g.height - ceiling;

            
        }
    }
    
}
