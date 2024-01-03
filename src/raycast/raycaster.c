/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:51:47 by bguillau          #+#    #+#             */
/*   Updated: 2024/01/03 17:51:49 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	raycast_launcher(t_info *info)
{
	t_raycast	rc;
	int			x;
	int			camerax;

	ft_bzero(&rc, sizeof(t_raycast));
	x = -1;
	while (++x < WIN_W)
	{
		camerax = 2 * x / (double)WIN_W - 1;
		rc.raydirx = info->dirx + info->planex + camerax;
		rc.raydiry = info->diry + info->planey + camerax;
		dda_prep(&rc, info->posx, info->posy);
		dda(&rc, info->map);
	}
	return (1);
}

void	post_dda_calculations();
