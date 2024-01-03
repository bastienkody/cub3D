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

void	maximap_key_movement(int keycode, t_info *info)
{
	const int	xmax = info->mw - 1;
	const int	ymax = info->mh - 1;

	if (keycode == XK_w && info->posy - 1 >= 0 && is_floor(0, -1, info))
		info->posy -= 1;
	else if (keycode == XK_s && info->posy + 1 <= ymax && is_floor(0, 1, info))
		info->posy += 1;
	else if (keycode == XK_a && info->posx - 1 >= 0 && is_floor(-1, 0, info))
		info->posx -= 1;
	else if (keycode == XK_d && info->posx + 1 <= xmax && is_floor(1, 0, info))
		info->posx += 1;
	else
		return ;
}
