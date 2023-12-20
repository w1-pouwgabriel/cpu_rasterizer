#include "App.h"

App::App() 
{
    init();
}

App::~App()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool App::init()
{
    //Initialization flag
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        window = SDL_CreateWindow( "Cpu_Rasterizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN );
        if(window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL) 
            {
                printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }
            else 
            {
                // Create an empty texture with the desired format, access, and dimensions
                texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
                if (texture == NULL)
                {
                    printf("Unable to create texture! SDL_Error: %s\n", SDL_GetError());
                    success = false;
                }
            }
        }

        //Other stuff that we need to initialze....
        frameBuffer.resize(WIDTH * HEIGHT, 0);
    }

    return success;
}

void App::Loop()
{
    SDL_Event e;
    bool quit = false;

    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
            else if (e.key.keysym.sym == SDLK_ESCAPE) // input handeling
                quit = true;
        }

        //Input handeling
        //Game logic

        // Render graphics
        Render();
    }
}

void App::Render()
{
    // Clear the frame buffer
    frameBuffer.clear();
    frameBuffer.resize(WIDTH * HEIGHT, 0);

    Line(100, 100, 200, 200, ConvertColor(255, 255, 255, 255));

    // Update SDL texture with the frame buffer
    SDL_UpdateTexture(texture, NULL, frameBuffer.data(), WIDTH * sizeof(Uint32));

    // Render to the screen
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

Uint32 App::ConvertColor(int r, int g, int b, int a)
{
    return (r << 24U) | (g << 16U) | (b << 8U) | a;
}

void App::Line(int x0, int y0, int x1, int y1, Uint32 Color)
{
    for (float t = 0.; t < 1.; t += .01) {
        int x = x0 + (x1 - x0) * t;
        int y = y0 + (y1 - y0) * t;
        frameBuffer.at(x + y * WIDTH) = Color;
    }
}
