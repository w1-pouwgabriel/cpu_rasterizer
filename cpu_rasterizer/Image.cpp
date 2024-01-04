#include "Image.h"
#include "Utils.h"
#include "DotObjModel.h"

#include <iostream>

Image::Image(int width, int height)
    : imageWidth(width), imageHeight(height)
{
    Clear();
}

Image::~Image()
{
    Clear();
}

void Image::Clear(Uint32 ClearColor)
{
    // Clear the frame buffer
    frameBuffer.clear();
    frameBuffer.resize(imageWidth * imageHeight, ClearColor);
}

Uint32* Image::GetData()
{
    return frameBuffer.data();
}

void Image::Set(int x, int y, Uint32 Color)
{
    if (x >= imageWidth || x <= 0 || y >= imageHeight || y <= 0) {
#ifdef _DEBUG
        std::cout << "Pixel coordinates are offscreen" << std::endl;
#endif
        return;
    }
    frameBuffer.at(x + y * imageWidth) = Color;
}

void Image::Line(int x0, int y0, int x1, int y1, Uint32 Color)
{
    bool steep = false;
    if (std::abs(x0 - x1) < std::abs(y0 - y1)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = std::abs(dy) * 2;
    int error2 = 0;
    int y = y0;
    for (int x = x0; x <= x1; x++) {
        if (steep) {
            Set(y, x, Color);
        }
        else {
            Set(x, y, Color);
        }
        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0 ? 1 : -1);
            error2 -= dx * 2;
        }
    }
}

void Image::Draw2DWireFrame(DotObjModel* model)
{
    for (int i = 0; i < model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        for (int j = 0; j < 3; j++) {
            Vec3f v0 = model->vert(face[j]);
            Vec3f v1 = model->vert(face[(j + 1) % 3]);
            int x0 = (v1.x + 1.) * imageWidth / 3;
            int y0 = (v1.y + 1.) * imageHeight / 3;
            int x1 = (v0.x + 1.) * imageWidth / 3;
            int y1 = (v0.y + 1.) * imageHeight / 3;
            Line(x0, y0, x1, y1, ConvertColor(rand() % 255, rand() % 255, rand() % 255, 255));
        }
    }
}