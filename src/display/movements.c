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
	return ((info->map[info->pposy + y_ofst][info->pposx + x_ofst] == '0'));
}

void	maximap_key_movement(int keycode, t_info *info)
{
	const int	xmax = info->mw - 1;
	const int	ymax = info->mh - 1;

	if (keycode == XK_w && info->pposy - 1 >= 0 && is_floor(0, -1, info))
		info->pposy -= 1;
	else if (keycode == XK_s && info->pposy + 1 <= ymax && is_floor(0, 1, info))
		info->pposy += 1;
	else if (keycode == XK_a && info->pposx - 1 >= 0 && is_floor(-1, 0, info))
		info->pposx -= 1;
	else if (keycode == XK_d && info->pposx + 1 <= xmax && is_floor(1, 0, info))
		info->pposx += 1;
	else
		return ;
	info->is_maximap = !info->is_maximap;
	maximap_display(info);
}
