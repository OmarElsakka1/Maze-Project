#include "../headers/header.h"

/**
 * changeColorIntensity - changing color intensity
 * based on a factor value between 0 and 1
 * @factor: the intensity factor
 * @color: the color for intensity
*/

void changeColorIntensity(color_t *color, float factor)
{
	color_t a = (*color & 0xFF000000);
	color_t r = (*color & 0x00FF0000) * factor;
	color_t g = (*color & 0x0000FF00) * factor;
	color_t b = (*color & 0x000000FF) * factor;

	*color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

/**
 * renderFloor - rendering floor projection
 *
 * @wall_bottom_pixel: the wall bottom pixel
 * @texelColor: teh texture color for current pixel
 * @x: the current element in the rays array
*/

void renderFloor(int wall_bottom_pixel, color_t *texelColor, int x)
{
	int y, texture_height, texture_width, texture_offset_y, texture_offset_x;
	float distance, ratio;

	texture_width = wallTextures[3].width;
	texture_height = wallTextures[3].height;

	for (y = wall_bottom_pixel - 1; y < SCREEN_HEIGHT; y++)
	{
		ratio = the_player.height / (y - SCREEN_HEIGHT / 2);
		distance = (ratio * PROJ_PLANE)
					/ cos(rays[x].rayAngle - the_player.rotationAngle);

		texture_offset_y = (int)abs((distance * sin(rays[x].rayAngle)) + the_player.y);
		texture_offset_x = (int)abs((distance * cos(rays[x].rayAngle)) + the_player.x);

		texture_offset_x = (int)(abs(texture_offset_x * texture_width / 30)
								% texture_width);
		texture_offset_y = (int)(abs(texture_offset_y * texture_height / 30)
								% texture_height);

		*texelColor = wallTextures[4].
					  texture_buffer[(texture_width * texture_offset_y) + texture_offset_x];
		drawPixel(x, y, *texelColor);
	}
}

/**
 * renderCeil - rendering Ceil projection
 * @wall_top_pixel: the wall top pixel
 * @texelColor: the texture color for current pixel
 * @x: the current element in the rays array
*/

void renderCeil(int wall_top_pixel, color_t *texelColor, int x)
{
	int y, texture_width, texture_height, texture_offset_y, texture_offset_x;

	texture_width = wallTextures[3].width;
	texture_height = wallTextures[3].height;

	for (y = 0; y < wall_top_pixel; y++)
	{
		float distance, ratio;

		ratio = the_player.height / (y - SCREEN_HEIGHT / 2);
		distance = (ratio * PROJ_PLANE)
					/ cos(rays[x].rayAngle - the_player.rotationAngle);

		texture_offset_y = (int)abs((-distance * sin(rays[x].rayAngle)) + the_player.y);
		texture_offset_x = (int)abs((-distance * cos(rays[x].rayAngle)) + the_player.x);

		texture_offset_x = (int)(abs(texture_offset_x * texture_width / 40)
								% texture_width);
		texture_offset_y = (int)(abs(texture_offset_y * texture_height / 40)
								% texture_height);

		*texelColor = wallTextures[6].
					  texture_buffer[(texture_width * texture_offset_y) + texture_offset_x];
		drawPixel(x, y, *texelColor);

	}
}

/**
 * renderWall - render wall projection
 *
*/
void renderWall(void)
{
	int x, y, tex_num, texture_width, texture_height,
		texture_offset_x, wall_bottom_pixel, wall_strip_height,
		wall_top_pixel, distance_from_top, texture_offset_y;
	float perp_distance, projected_wall_height;
	color_t texelColor;

	for (x = 0; x < NUM_RAYS; x++)
	{
		perp_distance = rays[x].distance * cos(rays[x].rayAngle
							- the_player.rotationAngle);
		projected_wall_height = (TILE_SIZE / perp_distance) * PROJ_PLANE;
		wall_strip_height = (int)projected_wall_height;
		wall_top_pixel = (SCREEN_HEIGHT / 2) - (wall_strip_height / 2);
		wall_top_pixel = wall_top_pixel < 0 ? 0 : wall_top_pixel;
		wall_bottom_pixel = (SCREEN_HEIGHT / 2) + (wall_strip_height / 2);
		wall_bottom_pixel = wall_bottom_pixel > SCREEN_HEIGHT
							? SCREEN_HEIGHT : wall_bottom_pixel;
		tex_num = rays[x].wallHitContent - 1;
		texture_width = wallTextures[tex_num].width;
		texture_height = wallTextures[tex_num].height;
		renderFloor(wall_bottom_pixel, &texelColor, x);
		renderCeil(wall_top_pixel, &texelColor, x);

		if (rays[x].wasHitVertical)
			texture_offset_x = (int)rays[x].wallHitY % TILE_SIZE;
		else
			texture_offset_x = (int)rays[x].wallHitX % TILE_SIZE;

		for (y = wall_top_pixel; y < wall_bottom_pixel; y++)
		{
			distance_from_top = y + (wall_strip_height / 2) - (SCREEN_HEIGHT / 2);
			texture_offset_y = distance_from_top *
								((float)texture_height / wall_strip_height);
			texelColor = wallTextures[tex_num].
						 texture_buffer[(texture_width * texture_offset_y) + texture_offset_x];
			if (rays[x].wasHitVertical)
				changeColorIntensity(&texelColor, 0.5);
			drawPixel(x, y, texelColor);
		}
	}
}
