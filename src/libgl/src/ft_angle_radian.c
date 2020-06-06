#include "libgl.h"

double ft_to_rad(double deg)
{
	return (deg * (PI / 180.0));
}

double ft_to_deg(double radian)
{
	return (radian * (180.0 / PI));
}

float ft_to_radf(float deg)
{
	return (deg * ((float)PI / 180.0f));
}

float ft_to_degf(float radian)
{
	return (radian * (180.0f / (float)PI));
}