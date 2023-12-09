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

	std::vector<int> frameBuffer;

	SDL_Texture* texture;
	SDL_Window* window;
	SDL_Renderer* renderer;
};