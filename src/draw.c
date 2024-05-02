#include "../headers/header.h"

/**
 * drawRect - drawing a rectangle
 * @x: x coordinate
 * @y: y coordinate
 * @width: the rectangle width
 * @height: the rectangle height
 * @color: the pixel color
*/

void drawRect(int x, int y, int width, int height, color_t color)
{
	int i, j;

	for (i = x; i <= (x + width); i++)
		for (j = y; j <= (y + height); j++)
			drawPixel(i, j, color);
}

/**
 * drawLine - drawing a line
 * @x0: x coordinate start
 * @y0: y coordinate start
 * @x1: x coordinate end
 * @y1: y coordinate end
 * @color: the pixel color
*/

void drawLine(int x0, int y0, int x1, int y1, color_t color)
{
	float x_increment, y_increment, current_x, current_y;
	int longest_side_length, delta_x,  delta_y;

	delta_x = (x1 - x0);
	delta_y = (y1 - y0);

	longest_side_length = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);

	x_increment = delta_x / (float)longest_side_length;
	y_increment = delta_y / (float)longest_side_length;

	current_x = x0;
	current_y = y0;

	for (int i = 0; i < longest_side_length; i++)
	{
		drawPixel(round(current_x), round(current_y), color);
		current_x += x_increment;
		current_y += y_increment;
	}
}