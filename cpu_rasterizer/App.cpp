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

    for (int x = 0; x < WIDTH; x++) {
        for (int y = 0; y < HEIGHT; y++) {
            frameBuffer.at(x + y * WIDTH) = 255;
        }
    }

    // Update SDL texture with the frame buffer
    SDL_UpdateTexture(texture, NULL, frameBuffer.data(), WIDTH * sizeof(Uint32));

    // Render to the screen
    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}
