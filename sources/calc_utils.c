#include "cub3d.h"

int	east_facing(double angle)
{
	// I mean only the part from corner to corner
	if (angle < PI / 4 || angle > (2 * PI - PI / 4))
		return (1);
	return (0);
}

int	west_facing(double angle)
{
	// I mean only the part from corner to corner
	if (angle > (PI - PI / 4) && angle < (PI + PI / 4))
		return (1);
	return (0);	
}

void	fish_eye_correction(t_player *player)
{
	if (player->sdX < player->sdY)
	{
		if (east_facing(player->ray_angle) || west_facing(player->ray_angle))
			player->sdX = cos(player->ray_angle) * player->sdX;
		else
			player->sdX = sin(player->ray_angle) * player->sdX;
	}
	else
	{
		if (east_facing(player->ray_angle) || west_facing(player->ray_angle))
			player->sdX = cos(player->ray_angle) * player->sdX;
		else
			player->sdX = sin(player->ray_angle) * player->sdX;
	}
}

void	get_wall_texture(t_player *player)
{
	if (player->sdX < player->sdY)
		if (player->ray_angle < PI)
			//wall texture is NORTH
		else
			//wall texture is SOUTH
	else
		if (player->ray_angle > PI / 2 || player->ray_angle < PI + PI / 2)
			//wall texture is EAST
		else
			//wall texture is WEST
}
