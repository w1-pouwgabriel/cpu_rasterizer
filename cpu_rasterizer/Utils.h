#pragma once
#include <SDL/SDL.h>

inline Uint32 ConvertColor(int r, int g, int b, int a)
{
    return (r << 24U) | (g << 16U) | (b << 8U) | a;
}