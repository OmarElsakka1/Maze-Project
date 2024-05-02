/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
See this link for this: 
https://discourse.libsdl.org/t/memory-usage-of-simple-sdl2-program-grows-linearly/36452*/

//SDL
#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

//This is the Screen dimension.
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(__attribute__((unused)) int argc, __attribute__((unused)) char* args[] )
{
    //The window we will render to
    SDL_Window* the_window = NULL;

    //This is the surface contained by the window
    SDL_Surface* screen_surface = NULL;

    //Initializing the SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "The SDL can not be initialized! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        //Creating window
        the_window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( the_window == NULL )
        {
            printf( "The window can not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Getting the window surface
            screen_surface = SDL_GetWindowSurface( the_window );

            //Filling the surface white
            SDL_FillRect( screen_surface, NULL, SDL_MapRGB( screen_surface->format, 0xFF, 0xFF, 0xFF ) );

            //Updating the surface
            SDL_UpdateWindowSurface( the_window );

            //getting the window to stay up
            SDL_Event e; bool quit = false; while( quit == false ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = true; } }
        }
    }

    //Destroying window
    SDL_DestroyWindow( the_window );

    //Quitting the SDL subsystems
    SDL_Quit();

    return 0;
}