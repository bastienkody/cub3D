/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:49:58 by bastienguil       #+#    #+#             */
/*   Updated: 2024/01/29 16:41:02 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/*
	Movements collision : only move if possible in x AND y. We may enable a
	'wall slide' effect by checking and updatating each direction separetly
	FRONT/BACK move dir : using player dir vector (=where player faces)
	LEFT/RIGHT : using player camera plane (=perfect perpendicular to dir)
	ROTATE : always possible
	GLITCH : impossible to get outside of map ; glitch to floor handled by
	checking : both int(floor(x)) and int(floor(y)) must change (=forcement en 
	diagonale) and perpendicular walls presence top left + top right (from pov)
*/

int	rotate(int keycode, t_info *info)
{
	const double	oldir_x = info->dirx;
	const double	oldplanex = info->planex;
	double			ang;

	ang = -M_PI / PI_DIVIDER;
	if (keycode == XK_Right)
		ang = M_PI / PI_DIVIDER;
	info->dirx = info->dirx * cos(ang) - info->diry * sin(ang);
	info->diry = oldir_x * sin(ang) + info->diry * cos(ang);
	info->planex = info->planex * cos(ang) - info->planey * sin(ang);
	info->planey = oldplanex * sin(ang) + info->planey * cos(ang);
	return (1);
}

int	wall_glitch(t_info *info, int x_offset, int y_offset)
{
	const int	x = (int)floor(info->posx);
	const int	y = (int)floor(info->posy);

	if (x_offset == x || y_offset == y)
		return (0);
	if (info->map[y_offset][x] == '1' && info->map[y][x_offset] == '1')
		return (1);
	return (0);
}

int	move(t_info *info, double x_offset, double y_offset)
{
	if (info->map[(int)floor(y_offset)][(int)floor(x_offset)] == '0')
	{
		if (wall_glitch(info, (int)floor(x_offset), (int)floor(y_offset)))
			return (0);
		info->posx = x_offset;
		info->posy = y_offset;
		return (1);
	}
	return (0);
}

/*	no need to redraw raycast if player could not moved/turned
	directionnal sprint: add '&& keycode == W' apres le check du shift	*/
void	key_movement(int keycode, t_info *info)
{
	bool	redraw;
	double	speed;

	redraw = false;
	speed = VELO_MOVE;
	if (info->keys[6])
		speed = VELO_SPRINT;
	if (keycode == XK_w)
		redraw = move(info, info->posx + info->dirx * speed, \
		info->posy + info->diry * speed);
	else if (keycode == XK_s)
		redraw = move(info, info->posx - info->dirx * speed, \
		info->posy - info->diry * speed);
	else if (keycode == XK_a)
		redraw = move(info, info->posx - info->planex * speed, \
		info->posy - info->planey * speed);
	else if (keycode == XK_d)
		redraw = move(info, info->posx + info->planex * speed, \
		info->posy + info->planey * speed);
	else
		redraw = rotate(keycode, info);
	if (!redraw)
		return ;
	raycast_launcher(info);
}
