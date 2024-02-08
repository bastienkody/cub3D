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

/*	add a step security to move to ensure player is always a bit away from wall
	step is set according to dir (going front/back) or plane (going sideway)
	if player goes backwards or right is it the opposite	
*/
void	update_step(t_info *info, int keycode, double *stepx, double *stepy)
{
	*stepx = MOVE_STEP_NUM;
	*stepy = MOVE_STEP_NUM;
	if (keycode == XK_w || keycode == XK_s)
	{
		if (info->dirx < 0)
			*stepx = -MOVE_STEP_NUM;
		if (info->diry < 0)
			*stepy = -MOVE_STEP_NUM;
	}
	if (keycode == XK_a || keycode == XK_d)
	{
		if (info->planex < 0)
			*stepx = -MOVE_STEP_NUM;
		if (info->planey < 0)
			*stepy = -MOVE_STEP_NUM;
	}
	if (keycode == XK_s || keycode == XK_a)
	{
		*stepx *= -1;
		*stepy *= -1;
	}
}

int	move_front_back(t_info *info, int keycode, double speed)
{
	double	x_ofs;
	double	y_ofs;
	double	stepy;
	double	stepx;

	update_step(info, keycode, &stepx, &stepy);
	x_ofs = info->dirx * speed;
	y_ofs = info->diry * speed;
	if (keycode == XK_s)
	{
		x_ofs *= -1;
		y_ofs *= -1;
	}
	//printf("x%f +%f, y%f +%f\n", info->posx, x_ofs + stepx, info->posy, y_ofs + stepy);
	if (info->map[(int)floor(info->posy + y_ofs + \
		stepy)][(int)floor(info->posx + x_ofs + stepx)] == '0')
	{
		info->posx += x_ofs;
		info->posy += y_ofs;
		return (1);
	}
	return (0);
}

int	move_sides(t_info *info, int keycode, double speed)
{
	double	x_ofs;
	double	y_ofs;
	double	stepy;
	double	stepx;

	update_step(info, keycode, &stepx, &stepy);
	x_ofs = info->planex * speed;
	y_ofs = info->planey * speed;
	if (keycode == XK_a)
	{
		x_ofs *= -1;
		y_ofs *= -1;
	}
	if (info->map[(int)floor(info->posy + y_ofs + \
		stepy)][(int)floor(info->posx + x_ofs + stepx)] == '0')
	{
		info->posx += x_ofs;
		info->posy += y_ofs;
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
