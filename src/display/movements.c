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

void	crouch_uncrouch(t_info *info)
{
	if (info->crouch)
		info->crouch = 0;
	else
		info->crouch = CROUCH_VAL;
	raycast_launcher(info);
	draw_minimap(info);
}

/*	always possible to rotate	*/
int	rotate(__attribute__((unused)) int keycode, t_info *info)
{
	const double	oldir_x = info->dirx;
	const double	oldplanex = info->planex;
	double			ang;

	ang = -VELO_R;
	if (keycode == XK_Right)
		ang = VELO_R;
	info->dirx = info->dirx * cos(ang) - info->diry * sin(ang);
	info->diry = oldir_x * sin(ang) + info->diry * cos(ang);
	info->planex = info->planex * cos(ang) - info->planey * sin(ang);
	info->planey = oldplanex * sin(ang) + info->planey *cos(ang);
	return (1);
}

/*	back or forward via player dir vector	*/
int	move_front_back_wards(int keycode, t_info *info)
{
	double	x_offset;
	double	y_offset;

	if (keycode == XK_w)
	{
		x_offset = info->posx + info->dirx * VELO_M;
		y_offset = info->posy + info->diry * VELO_M;
		if (info->map[(int)floor(y_offset)][(int)floor(x_offset)] == '0')
		{
			info->posx = x_offset;
			info->posy = y_offset;
			return (1);
		}
	}
	else if (keycode == XK_s)
	{
		x_offset = info->posx - info->dirx * VELO_M;
		y_offset = info->posy - info->diry * VELO_M;
		if (info->map[(int)floor(y_offset)][(int)floor(x_offset)] == '0')
		{
			info->posx = x_offset;
			info->posy = y_offset;
			return (1);
		}
	}
	return (0);
}

/*	side via player plane (always perpendiculaire to player dir)	*/
int	move_sides(int keycode, t_info *info)
{
	double	x_offset;
	double	y_offset;

	if (keycode == XK_a)
	{
		x_offset = info->posx - info->planex * VELO_M;
		y_offset = info->posy - info->planey * VELO_M;
		if (info->map[(int)floor(y_offset)][(int)floor(x_offset)] == '0')
		{
			info->posx = x_offset;
			info->posy = y_offset;
			return (1);
		}
	}
	else if (keycode == XK_d)
	{
		x_offset = info->posx + info->planex * VELO_M;
		y_offset = info->posy + info->planey * VELO_M;
		if (info->map[(int)floor(y_offset)][(int)floor(x_offset)] == '0')
		{
			info->posx = x_offset;
			info->posy = y_offset;
			return (1);
		}
	}
	return (0);
}

/*	redraw raycast only if player has moved/turned	*/
void key_movement(int keycode, t_info *info)
{
	bool	redraw;

	redraw = false;
	if (keycode == XK_w || keycode == XK_s)
		redraw = move_front_back_wards(keycode, info);
	else if ((keycode == XK_a || keycode == XK_d))
		redraw = move_sides(keycode, info);
	else
		redraw = rotate(keycode, info);
	if (!redraw)
		return ;
	raycast_launcher(info);
	draw_minimap(info);
}


