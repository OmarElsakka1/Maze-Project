#include "../headers/header.h"

ray_t rays[NUM_RAYS];

static bool found_horz_wall_hit, found_vert_wall_hit;
static float horz_wall_hit_x, horz_wall_hit_y, vert_wall_hit_x, vert_wall_hit_y;
static int horz_wall_content, vert_wall_content;


/**
 * horzIntersection - Finding horizontal intersection with the wall
 * @rayAngle: the current ray angle
 *
 */

void horzIntersection(float rayAngle)
{
	float next_horz_touch_x, next_horz_touch_y, x_intercept, y_intercept, x_step, y_step;

	found_horz_wall_hit = false;
	horz_wall_hit_x = horz_wall_hit_y = horz_wall_content = 0;

	y_intercept = floor(the_player.y / TILE_SIZE) * TILE_SIZE;
	y_intercept += isRayFacingDown(rayAngle) ? TILE_SIZE : 0;

	x_intercept = the_player.x + (y_intercept - the_player.y) / tan(rayAngle);

	y_step = TILE_SIZE;
	y_step *= isRayFacingUp(rayAngle) ? -1 : 1;
	x_step = TILE_SIZE / tan(rayAngle);
	x_step *= (isRayFacingLeft(rayAngle) && x_step > 0) ? -1 : 1;
	x_step *= (isRayFacingRight(rayAngle) && x_step < 0) ? -1 : 1;
	next_horz_touch_x = x_intercept;
	next_horz_touch_y = y_intercept;

	while (isInsideMap(next_horz_touch_x, next_horz_touch_y))
	{
		float xToCheck = next_horz_touch_x;
		float yToCheck = next_horz_touch_y + (isRayFacingUp(rayAngle) ? -1 : 0);

		if (DetectCollision(xToCheck, yToCheck))
		{
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			horz_wall_content = getMapValue((int)floor(yToCheck / TILE_SIZE),
									   (int)floor(xToCheck / TILE_SIZE));
			found_horz_wall_hit = true;
			break;
		}
		next_horz_touch_x += x_step;
		next_horz_touch_y += y_step;
	}
}

/**
 * vertIntersection - Finding vertical intersection with the wall
 * @rayAngle: the current ray angle
 *
 */

void vertIntersection(float rayAngle)
{
	float next_vert_touch_x, next_vert_touch_y;
	float x_intercept, y_intercept, x_step, y_step;

	found_vert_wall_hit = false;
	vert_wall_hit_x = 0;
	vert_wall_hit_y = 0;
	vert_wall_content = 0;

	x_intercept = floor(the_player.x / TILE_SIZE) * TILE_SIZE;
	x_intercept += isRayFacingRight(rayAngle) ? TILE_SIZE : 0;
	y_intercept = the_player.y + (x_intercept - the_player.x) * tan(rayAngle);

	x_step = TILE_SIZE;
	x_step *= isRayFacingLeft(rayAngle) ? -1 : 1;
	y_step = TILE_SIZE * tan(rayAngle);
	y_step *= (isRayFacingUp(rayAngle) && y_step > 0) ? -1 : 1;
	y_step *= (isRayFacingDown(rayAngle) && y_step < 0) ? -1 : 1;
	next_vert_touch_x = x_intercept;
	next_vert_touch_y = y_intercept;

	while (isInsideMap(next_vert_touch_x, next_vert_touch_y))
	{
		float xToCheck = next_vert_touch_x + (isRayFacingLeft(rayAngle) ? -1 : 0);
		float yToCheck = next_vert_touch_y;

		if (DetectCollision(xToCheck, yToCheck))
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			vert_wall_content = getMapValue((int)floor(yToCheck / TILE_SIZE),
									   (int)floor(xToCheck / TILE_SIZE));
			found_vert_wall_hit = true;
			break;
		}
		next_vert_touch_x += x_step;
		next_vert_touch_y += y_step;
	}
}

/**
 * castRay - casting of each ray
 * @rayAngle: the current ray angle
 * @stripId: the ray strip identifier
 */

void castRay(float rayAngle, int stripId)
{
	float horz_hit_distance, vert_hit_distance;

	rayAngle = remainder(rayAngle, TWO_PI);
	if (rayAngle < 0)
		rayAngle = TWO_PI + rayAngle;

	horzIntersection(rayAngle);

	vertIntersection(rayAngle);

	horz_hit_distance = found_horz_wall_hit
		? distanceBetweenPoints(the_player.x, the_player.y, horz_wall_hit_x, horz_wall_hit_y)
		: FLT_MAX;
	vert_hit_distance = found_vert_wall_hit
		? distanceBetweenPoints(the_player.x, the_player.y, vert_wall_hit_x, vert_wall_hit_y)
		: FLT_MAX;

	if (vert_hit_distance < horz_hit_distance)
	{
		rays[stripId].distance = vert_hit_distance;
		rays[stripId].wallHitX = vert_wall_hit_x;
		rays[stripId].wallHitY = vert_wall_hit_y;
		rays[stripId].wallHitContent = vert_wall_content;
		rays[stripId].wasHitVertical = true;
		rays[stripId].rayAngle = rayAngle;
	}
	else
	{
		rays[stripId].distance = horz_hit_distance;
		rays[stripId].wallHitX = horz_wall_hit_x;
		rays[stripId].wallHitY = horz_wall_hit_y;
		rays[stripId].wallHitContent = horz_wall_content;
		rays[stripId].wasHitVertical = false;
		rays[stripId].rayAngle = rayAngle;
	}

}

/**
 * castAllRays - cast of all rays
 *
 */

void castAllRays(void)
{

	for (int col = 0; col < NUM_RAYS; col++)
	{
		float rayAngle = the_player.rotationAngle +
							atan((col - NUM_RAYS / 2) / PROJ_PLANE);
		castRay(rayAngle, col);
	}
}

/**
 * renderRays - draw all the rays
 *
 */

void renderRays(void)
{

	for (int i = 0; i < NUM_RAYS; i += 50)
	{
		drawLine(
			the_player.x * MINIMAP_SCALE_FACTOR,
			the_player.y * MINIMAP_SCALE_FACTOR,
			rays[i].wallHitX * MINIMAP_SCALE_FACTOR,
			rays[i].wallHitY * MINIMAP_SCALE_FACTOR,
			0xFF0000FF
		);
	}
}
