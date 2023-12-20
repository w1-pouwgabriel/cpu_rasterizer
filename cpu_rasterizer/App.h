#pragma once

const int WIDTH = 640;
const int HEIGHT = 480;

#include <SDL/SDL.h>
#include <vector>

class App {

public:
	App();
	~App();

	bool init();
	void Loop();

private:
	void Render();
	Uint32 ConvertColor(int r, int g, int b, int a);
	void Line(int x0, int y0, int x1, int y1, Uint32 Color);

	std::vector<Uint32> frameBuffer;

	SDL_Texture* texture;
	SDL_Window* window;
	SDL_Renderer* renderer;
};