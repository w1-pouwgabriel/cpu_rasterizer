#pragma once
#include <SDL/SDL.h>
#include <vector>

#include "DotObjModel.h"

class Image
{
public:
	Image(int width = 720, int height = 480);
	~Image();

	void Clear(Uint32 ClearColor = 0);
	Uint32* GetData();
	void Line(int x0, int y0, int x1, int y1, Uint32 Color);

	//Shit funcs
	void Draw2DWireFrame(DotObjModel* model);
private:
	void Set(int x, int y, Uint32 Color);

	std::vector<Uint32> frameBuffer;
	int imageWidth, imageHeight;
};

