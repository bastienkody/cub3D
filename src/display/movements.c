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

/*	always possible to rotate	*/
int	rotate(int keycode, t_info *info)
{
	const double	oldir_x = info->dirx;
	const double	oldplanex = info->planex;
	double			ang;

	ang = -VELO_ROTATE;
	if (keycode == XK_Right)
		ang = VELO_ROTATE;
	info->dirx = info->dirx * cos(ang) - info->diry * sin(ang);
	info->diry = oldir_x * sin(ang) + info->diry * cos(ang);
	info->planex = info->planex * cos(ang) - info->planey * sin(ang);
	info->planey = oldplanex * sin(ang) + info->planey * cos(ang);
	return (1);
}

/*	FRONT/BACK/SIDE Movements collision : only move if possible in x AND y
	This can be changed by checking and updatating each direction separetly 
	Dont know whats better lets discuss together	*/

/*	sprint only in forwrd movement (keys[6] == Lshift)	*/
int	move_frontwards(t_info *info)
{
	double	x_offset;
	double	y_offset;

	x_offset = info->posx + info->dirx * VELO_MOVE;
	y_offset = info->posy + info->diry * VELO_MOVE;
	if (info->keys[6])
	{
		x_offset = info->posx + info->dirx * VELO_SPRINT;
		y_offset = info->posy + info->diry * VELO_SPRINT;
	}
	printf("maptile[%f,%i][%f,%i]=%c\n", y_offset, (int)floor(y_offset), x_offset, (int)floor(x_offset), info->map[(int)floor(y_offset)][(int)floor(x_offset)]);
	if (info->map[(int)floor(y_offset)][(int)floor(x_offset)] == '0')
	{
		info->posx = x_offset;
		info->posy = y_offset;
		return (1);
	}
	return (0);
}

int	move_backwards(t_info *info)
{
	const double	x_offset = info->posx - info->dirx * VELO_MOVE;
	const double	y_offset = info->posy - info->diry * VELO_MOVE;

	printf("maptile[%f,%i][%f,%i]=%c\n", y_offset, (int)floor(y_offset), x_offset, (int)floor(x_offset), info->map[(int)floor(y_offset)][(int)floor(x_offset)]);
	if (info->map[(int)floor(y_offset)][(int)floor(x_offset)] == '0')
	{
		info->posx = x_offset;
		info->posy = y_offset;
		return (1);
	}
	return (0);
}

/*	side via player plane (always perpendiculaire to player dir)	*/
int	move_sides(int keycode, t_info *info)
{
	double	offset[2];

	if (keycode == XK_a)
	{
		offset[0] = info->posx - info->planex * VELO_MOVE;
		offset[1] = info->posy - info->planey * VELO_MOVE;
		if (info->map[(int)floor(offset[1])][(int)floor(offset[0])] == '0')
		{
			info->posx = offset[0];
			info->posy = offset[1];
			return (1);
		}
	}
	else if (keycode == XK_d)
	{
		offset[0] = info->posx + info->planex * VELO_MOVE;
		offset[1] = info->posy + info->planey * VELO_MOVE;
		if (info->map[(int)floor(offset[1])][(int)floor(offset[0])] == '0')
		{
			info->posx = offset[0];
			info->posy = offset[1];
			return (1);
		}
	}
	return (0);
}

/*	redraw raycast only if player has moved/turned	*/
void	key_movement(int keycode, t_info *info)
{
	bool	redraw;

	redraw = false;
	if (keycode == XK_w)
		redraw = move_frontwards(info);
	else if (keycode == XK_s)
		redraw = move_backwards(info);
	else if ((keycode == XK_a || keycode == XK_d))
		redraw = move_sides(keycode, info);
	else
		redraw = rotate(keycode, info);
	if (!redraw)
		return ;
	raycast_launcher(info);
}
