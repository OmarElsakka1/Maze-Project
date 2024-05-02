#include "../headers/header.h"

bool the_game_running = false;
int the_ticks_last_frame;
player_t the_player;

/**
 * setup_game - initializing the player variables and loading wall textures
 *
*/

void setup_game(void)
{

	the_player.x = SCREEN_WIDTH / 2;
	the_player.y = SCREEN_HEIGHT / 2;
	the_player.width = 1;
	the_player.height = 30;
	the_player.walkDirection = 0;
	the_player.walkSpeed = 100;
	the_player.turnDirection = 0;
	the_player.turnSpeed = 45 * (PI / 180);
	the_player.rotationAngle = PI / 2;
	WallTexturesready();
}


/**
 * update_game - update_game delta time, the ticks last frame
 *          the player movement and the ray casting
 *
*/
void update_game(void)
{
	float DeltaTime;
	int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - the_ticks_last_frame);

	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH)
	{
		SDL_Delay(timeToWait);
	}
	DeltaTime = (SDL_GetTicks() - the_ticks_last_frame) / 1000.0f;

	the_ticks_last_frame = SDL_GetTicks();

	movePlayer(DeltaTime);
	castAllRays();
}

/**
 * render - calling all functions needed for on-screen rendering
 *
*/

void render_game(void)
{
	clearColorBuffer(0xFF000000);

	renderWall();

	renderMap();
	renderRays();
	renderPlayer();

	renderColorBuffer();
}

/**
 * Destroy - free wall textures and destroy window
 *
*/
void destroy_game(void)
{
	freeWallTextures();
	destroyWindow();
}

/**
 * main - main function
 * Return: 0
*/

int main(void)
{
	the_game_running = initializeWindow();

	setup_game();

	while (the_game_running)
	{
		handleInput();
		update_game();
		render_game();
	}
	destroy_game();
	return (0);
}