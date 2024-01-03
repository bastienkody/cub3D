/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:55:31 by bguillau          #+#    #+#             */
/*   Updated: 2024/01/03 18:55:33 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	dda_prep(t_raycast *rc, int posx, int posy)
{
	rc->deltax = abs(1 / rc->raydirx); // div 0 possible
	rc->deltay = abs(1 / rc->raydiry); // div 0 possible

	if(rc->raydirx < 0)
	{
		rc->stepx = -1;
		rc->sidex = (posx - rc->mapx) * rc->deltax;
	}
	else
	{
		rc->stepx = 1;
		rc->sidex = (rc->mapx + 1.0 - posx) * rc->deltax;
	}
	if(rc->raydiry < 0)
	{
		rc->stepy = -1;
		rc->sidey = (posy - rc->mapx) * rc->deltay;
	}
	else
	{
		rc->stepy = 1;
		rc->sidey = (rc->mapy + 1.0 - posy) * rc->deltay;
	}
}

void	dda(t_raycast *rc, char **map)
{
	bool	hit; // no need of this bool if mapcheck in while ?

	hit = false;
	while (!hit)
	{
		if (rc->sidex < rc->sidey)
		{
			rc->sidex += rc->deltax;
			rc->mapx += rc->stepx;
			rc->side = 0;
		}
		else
		{
			rc->sidey += rc->deltay;
			rc->mapy += rc->stepy;
			rc->side = 1;
		}
	if (map[rc->mapy][rc->mapx] > 0)
		hit = true;
	}
	// perpwall dist calculation here ?
}
