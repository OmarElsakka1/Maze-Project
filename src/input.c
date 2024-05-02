#include "../headers/header.h"

/**
 * SDL_KEYDOWN_FUNC - the process input when a key is down
 * @the_event: union containing structures for the different event types
*/

void SDL_KEYDOWN_FUNC(SDL_Event the_event)
{
	if (the_event.key.keysym.sym == SDLK_ESCAPE)
		GameRunning = false;
	if (the_event.key.keysym.sym == SDLK_UP)
		the_player.walkDirection = +1;
	if (the_event.key.keysym.sym == SDLK_DOWN)
		the_player.walkDirection = -1;
	if (the_event.key.keysym.sym == SDLK_RIGHT)
		the_player.turnDirection = +1;
	if (the_event.key.keysym.sym == SDLK_LEFT)
		the_player.turnDirection = -1;
	if (the_event.key.keysym.sym == SDLK_w)
		the_player.walkDirection = +1;
	if (the_event.key.keysym.sym == SDLK_s)
		the_player.walkDirection = -1;
	if (the_event.key.keysym.sym == SDLK_a)
		the_player.turnDirection = -1;
	if (the_event.key.keysym.sym == SDLK_d)
		the_player.turnDirection = +1;
}

/**
 * SDL_KEYUP_FUNC - process input when a key is up
 * @the_event: union containing structures for the different event types
*/

void SDL_KEYUP_FUNC(SDL_Event the_event)
{
	if (the_event.key.keysym.sym == SDLK_UP)
		the_player.walkDirection = 0;
	if (the_event.key.keysym.sym == SDLK_DOWN)
		the_player.walkDirection = 0;
	if (the_event.key.keysym.sym == SDLK_RIGHT)
		the_player.turnDirection = 0;
	if (the_event.key.keysym.sym == SDLK_LEFT)
		the_player.turnDirection = 0;
	if (the_event.key.keysym.sym == SDLK_w)
		the_player.walkDirection = 0;
	if (the_event.key.keysym.sym == SDLK_s)
		the_player.walkDirection = 0;
	if (the_event.key.keysym.sym == SDLK_a)
		the_player.turnDirection = 0;
	if (the_event.key.keysym.sym == SDLK_d)
		the_player.turnDirection = 0;
}

/**
 * handleInput - process input from the keyboard
 *
*/
void handleInput(void)
{
	SDL_Event the_event;

	SDL_PollEvent(&the_event);

	if (the_event.type == SDL_QUIT)
		GameRunning = false;
	else if (the_event.type == SDL_KEYDOWN)
		SDL_KEYDOWN_FUNC(the_event);
	else if (the_event.type == SDL_KEYUP)
		SDL_KEYUP_FUNC(the_event);
}
