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

int	is_floor(double newx, double newy, t_info *info)
{
	if (info->dirx >= 0)
		newx = ceil(newx);
	else
		newx = floor(newx);
	if (info->diry >= 0)
		newy = ceil(newy);
	else
		newy = floor(newy);
	printf("is floor(map[%0.f][%0.f])=%i\n", newy, newx, info->map[(int)newy][(int)newx] - '0');
	return ((info->map[(int)newy][(int)newx] == '0'));
}

void key_movement(int keycode, t_info *info)
{
	const double	xmax = info->mw - 1;
	const double	ymax = info->mh - 1;
	double			xofs;
	double			yofs;

	if (keycode == XK_w)
	{
		xofs = info->posx + info->dirx * VELO_M;
		yofs = info->posy + info->diry * VELO_M;
		if (xofs >= 0 && xofs <= xmax && yofs >= 0 && yofs <= ymax && is_floor(xofs, yofs, info))
		{
			info->posx = xofs;
			info->posy = yofs;
		}
	}
	else if (keycode == XK_s)
	{
		xofs = info->posx - info->dirx * VELO_M;
		yofs = info->posy - info->diry * VELO_M;
		if (xofs >= 0 && xofs < xmax && yofs >= 0 && yofs < ymax  && is_floor(xofs, yofs, info))
		{
			info->posx = xofs;
			info->posy = yofs;
		}
	}
	else if (keycode == XK_a)
	{
		xofs = info->posx - info->planex * VELO_M;
		yofs = info->posy - info->planey * VELO_M;
		if (xofs >= 0 && xofs < xmax && yofs >= 0 && yofs < ymax && is_floor(xofs, yofs, info))
		{
			info->posx = xofs;
			info->posy = yofs;
		}
	}
	else if (keycode == XK_d)
	{
		xofs = info->posx + info->planex * VELO_M;
		yofs = info->posy + info->planey * VELO_M;
		if (xofs >= 0 && xofs < xmax && yofs >= 0 && yofs < ymax && is_floor(xofs, yofs, info))
		{
			info->posx = xofs;
			info->posy = yofs;
		}
	}
	else
		return ;
	raycast_launcher(info);
	draw_minimap(info);
}

void	rotate(int keycode, t_info *info)
{
	const double	oldir_x = info->dirx;
	const double	oldplanex = info->planex;
	double			ang;

	ang = VELO_R;
	if (keycode == XK_Right)
		ang = -VELO_R;
	info->dirx = info->dirx* cos(ang) - info->diry * sin(ang);
	info->diry = oldir_x * sin(ang) + info->diry * cos(ang);
	info->planex = info->planex * cos(ang) - info->planey * sin(ang);
	info->planey = oldplanex * sin(ang) + info->planey *cos(ang);
	raycast_launcher(info);
	draw_minimap(info);
}
