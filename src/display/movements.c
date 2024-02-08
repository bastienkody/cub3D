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
	MOVE COLLISIONS : checking and updating each direction separetly!
	To toggle off 'wall slide' effect : both x AND y offset must lead to floor
	FRONT/BACK move dir : using player dir vector (=where player faces)
	LEFT/RIGHT : using player camera plane (=perfect perpendicular to dir)
	STEP : add a security to move to ensure player is always a bit away (0.2)
	from walls. Step is set with dir (going front/back) or plane (going sideway)
	if player goes backwards or leftside is it the opposite.
	ROTATE : always possible
	REDRAW : only if a move had occured. bool is mod in each function
	GLITCH (no need since step) :glitch to floor handled by checking : 
	both int(floor(x)) and int(floor(y)) must change (=forcement en diagonale) 
	and perpendicular walls presence top left + top right (from pov)
*/

void	rotate(int keycode, t_info *info, bool *redraw)
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
	*redraw = true;
}

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

void	move_front_back(t_info *info, int keycode, double speed, bool *redraw)
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
	if (info->map[(int)floor(info->posy + y_ofs + stepy)] \
	[(int)floor(info->posx)] == '0')
	{
		info->posy += y_ofs;
		*redraw = true;
	}
	if (info->map[(int)floor(info->posy)] \
	[(int)floor(info->posx + x_ofs + stepx)] == '0')
	{
		info->posx += x_ofs;
		*redraw = true;
	}
}

void	move_sides(t_info *info, int keycode, double speed, bool *redraw)
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
	if (info->map[(int)floor(info->posy + y_ofs + stepy)] \
	[(int)floor(info->posx)] == '0')
	{
		info->posy += y_ofs;
		*redraw = true;
	}
	if (info->map[(int)floor(info->posy)] \
	[(int)floor(info->posx + x_ofs + stepx)] == '0')
	{
		info->posx += x_ofs;
		*redraw = true;
	}
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
		move_front_back(info, keycode, speed, &redraw);
	else if (keycode == XK_a || keycode == XK_d)
		move_sides(info, keycode, speed, &redraw);
	else
		rotate(keycode, info, &redraw);
	if (!redraw)
		return ;
	raycast_launcher(info);
}
