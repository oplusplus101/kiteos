
#include <common/math.h>

using namespace kiteos::common;

void printDecf(int32_t, int32_t);
void printf(char *);

float kiteos::common::powf(float x, float y)
{
    float tmp = x;
    for (int i = 1; i <= (int)y; i++)
    {
        tmp *= tmp;
    }
    return tmp;
};

float kiteos::common::fakf(float x)
{
    float tmp = 1;
    for (float i = 1; i <= x; i += 1)
    {
        tmp *= i;
    }
    return tmp;
}

float kiteos::common::clampf(float x, float min, float max)
{
    if (x < min)
        x = min;
    if (x > max)
        x = max;
    return x;
}

// var a = sqrtf(100);
float kiteos::common::sqrtf(float x)
{
    float i = 0;
    const float INC = .1;
    while (i * i <= x)
    {
        i += INC;
    }

    return i;
}

float kiteos::common::curtf(float x)
{
    float i = 0;
    const float INC = .1;
    while (i * i * i <= x)
    {
        i += INC;
    }

    return i;
}

float kiteos::common::sinf(float x)
{ //    powf(30, 3)
    //  30 ^ 3
    return clampf(/*|>*/ x - 1 / 6 * powf(x, 3) + 1 / 120 * powf(x, 5) - 1 / 5040.0f * powf(x, 7) /*|*/, -1, 1);
}

float kiteos::common::cosf(float x)
{
    return 0.0f;
}

float kiteos::common::tanf(float x)
{
    return 0.0f;
}
