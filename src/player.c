#include "../headers/header.h"


/**
 * movePlayer - setting the next position of the player
 * @DeltaTime: the time elapsed since the last frame
*/

void movePlayer(float DeltaTime)
{
	float moveStep, newPlayerX, newPlayerY;

	the_player.rotationAngle += the_player.turnDirection * the_player.turnSpeed * DeltaTime;
	moveStep = the_player.walkDirection * the_player.walkSpeed * DeltaTime;

	newPlayerX = the_player.x + cos(the_player.rotationAngle) * moveStep;
	newPlayerY = the_player.y + sin(the_player.rotationAngle) * moveStep;

	if (!DetectCollision(newPlayerX, newPlayerY))
	{
		the_player.x = newPlayerX;
		the_player.y = newPlayerY;
	}
}

/**
 * renderPlayer - render the player
 *
*/

void renderPlayer(void)
{
	drawRect(
		the_player.x * MINIMAP_SCALE_FACTOR,
		the_player.y * MINIMAP_SCALE_FACTOR,
		the_player.width * MINIMAP_SCALE_FACTOR,
		the_player.height * MINIMAP_SCALE_FACTOR,
		0xFFFFFFFF
	);
}