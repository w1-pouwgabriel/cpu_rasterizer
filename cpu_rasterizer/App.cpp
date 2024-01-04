#include "App.h"
#include "Utils.h"

#include <iostream>
#include <ctime> 
#include <chrono>

App::App() 
{
    Init();
}

App::~App()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool App::Init()
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
                else 
                {
                    frameBuffer = Image(WIDTH, HEIGHT);
                }
            }
        }
    }

    return success;
}

void App::Loop()
{
    SDL_Event e;
    bool quit = false;

    while (!quit)
    {
        auto start = std::chrono::system_clock::now();
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
        frameBuffer.Clear();
        Render();

        auto end = std::chrono::system_clock::now();

#ifdef _DEBUG
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::time_t end_time = std::chrono::system_clock::to_time_t(end);

        std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
#endif
    }
}

void App::Render()
{
    //frameBuffer.Line(rand() % WIDTH, rand() % HEIGHT, rand() % WIDTH, rand() % HEIGHT, ConvertColor(255, 255, 255, 255));
    auto model = DotObjModel("Assets/african_head.obj");
    frameBuffer.Draw2DWireFrame(&model);

    // Update SDL texture with the frame buffer
    SDL_UpdateTexture(texture, NULL, frameBuffer.GetData(), WIDTH * sizeof(Uint32));

    // Render to the screen
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}