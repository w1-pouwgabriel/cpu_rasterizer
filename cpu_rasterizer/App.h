#pragma once

const int WIDTH = 640;
const int HEIGHT = 480;

#include <SDL/SDL.h>
#include "Image.h"

class App {

public:
	App();
	~App();

	bool Init();
	void Loop();

private:
	void Render();

	Image frameBuffer;

	SDL_Texture* texture;
	SDL_Window* window;
	SDL_Renderer* renderer;
};