#include "../headers/header.h"

/**
 * distanceBetweenPoints - Finding the horizontal intersection with the wall
 * @x1: x coordinate of starting point
 * @y1: y coordinate of starting point
 * @x2: x coordinate of end point
 * @y2: y coordinate of end point
 * Return: the distance between two points
 */

float distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2)));
}

/**
 * isRayFacingDown - checking if the ray is facing down
 * @angle: the current ray angle
 * Return: true or false
 */

bool isRayFacingDown(float angle)
{
	return (angle > 0 && angle < PI);
}

/**
 * isRayFacingUp - checking if the ray is facing up
 * @angle: the current ray angle
 * Return: true or false
 */

bool isRayFacingUp(float angle)
{
	return (!isRayFacingDown(angle));
}

/**
 * isRayFacingRight - checking if the ray is facing to the right
 * @angle: the current ray angle
 * Return: true or false
 */

bool isRayFacingRight(float angle)
{
	return (angle < 0.5 * PI || angle > 1.5 * PI);
}

/**
 * isRayFacingLeft - checking if the ray is facing to the right
 * @angle: the current ray angle
 * Return: true or false
 */

bool isRayFacingLeft(float angle)
{
	return (!isRayFacingRight(angle));
}
