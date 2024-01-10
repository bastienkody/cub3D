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

int	is_floor(int x_ofst, int y_ofst, t_info *info)
{
	return ((info->map[(int)info->posy + y_ofst][(int)info->posx + x_ofst] == '0'));
}

void key_movement(int keycode, t_info *info)
{
	const double	xmax = info->mw - 1;
	const double	ymax = info->mh - 1;

	if (keycode == XK_w && info->posy - VELO_M >= 0 && is_floor(0, -VELO_M, info))
		info->posy -= VELO_M;
	else if (keycode == XK_s && info->posy + VELO_M <= ymax && is_floor(0, VELO_M, info))
		info->posy += VELO_M;
	else if (keycode == XK_a && info->posx - VELO_M >= 0 && is_floor(-VELO_M, 0, info))
		info->posx -= VELO_M;
	else if (keycode == XK_d && info->posx + VELO_M <= xmax && is_floor(VELO_M, 0, info))
		info->posx += VELO_M;
	else
		return ;
	raycast_launcher(info);
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
}