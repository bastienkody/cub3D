/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastienguillaume <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 15:49:58 by bastienguilla     #+#    #+#             */
/*   Updated: 2023/12/30 15:50:01 by bastienguilla    ###   ########.fr       */
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
		return (printf("glitch\n"),  1);
	return (0);
}

int	move_front_back(t_info *info, int keycode, double speed)
{
	double	x_ofs;
	double	y_ofs;
	double	step;

	step = MOVE_STEP_NUM;
	x_ofs = info->dirx * speed;
	y_ofs = info->diry * speed;
	if (keycode == XK_s)
	{
		x_ofs *= -1;
		y_ofs *= -1;
		step *= -1;
	}
	printf("x%f +%f, y%f +%f\n", info->posx, x_ofs + step, info->posy, y_ofs + step);
	if (info->map[(int)floor(info->posy + y_ofs + \
		step)][(int)floor(info->posx + x_ofs + step)] == '0')
	{
		if (wall_glitch(info, (int)floor(info->posx + x_ofs * MOVE_STEP), \
			(int)floor(info->posy + y_ofs * MOVE_STEP)))
			return (0);
		info->posx += x_ofs;
		info->posy += y_ofs;
		return (1);
	}
	return (0);
}

int	move_sides(t_info *info, int keycode, double speed)
{
	double	x_step;
	double	y_step;

	x_step = info->planex * speed;
	y_step = info->planey * speed;
	if (keycode == XK_a)
	{
		x_step *= -1;
		y_step *= -1;
	}
	if (info->map[(int)floor(info->posy + y_step * \
		MOVE_STEP)][(int)floor(info->posx + x_step * MOVE_STEP)] == '0')
	{
		if (wall_glitch(info, (int)floor(info->posx + x_step * MOVE_STEP), \
			(int)floor(info->posy + y_step * MOVE_STEP)))
			return (0);
		info->posx += x_step;
		info->posy += y_step;
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
	if (keycode == XK_w || keycode == XK_s)
		redraw = move_front_back(info, keycode, speed);
	else if (keycode == XK_a || keycode == XK_d)
		redraw = move_sides(info, keycode, speed);
	else
		redraw = rotate(keycode, info);
	if (!redraw)
		return ;
	raycast_launcher(info);
}
