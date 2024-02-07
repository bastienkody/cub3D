/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastienguillaume <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 18:05:52 by bastienguilla     #+#    #+#             */
/*   Updated: 2023/12/30 18:05:54 by bastienguilla    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/*	192x192 screen on win at 20,20, ppos centered	*/

void	mini_raycast_calculation(t_info *info, t_raycast *rc, int x)
{
	double		camerax;

	camerax = 2 * x / (double)WIN_W - 1;
	rc->mapx = (int)info->posx;
	rc->mapy = (int)info->posy;
	rc->raydirx = info->dirx + info->planex * camerax;
	rc->raydiry = info->diry + info->planey * camerax;
	dda_prep(rc, info->posx, info->posy);
	dda(rc, info->map);
	if (rc->side == 0)
		rc->pwall = rc->sidex - rc->deltax;
	else
		rc->pwall = rc->sidey - rc->deltay;
}

void	draw_cone_raycast(t_info *info)
{
	t_raycast	rc;
	int			x;
	double		xpos;
	double		ypos;
	int			point[2];

	ft_bzero(&rc, sizeof(t_raycast));
	x = -1;
	while (++x < WIN_W)
	{
		mini_raycast_calculation(info, &rc, x);
		xpos = (rc.raydirx * rc.pwall * MNAP_TS);
		ypos = (rc.raydiry * rc.pwall * MNAP_TS);
		point[0] = (int)round(MNAP_S / 2 + xpos);
		point[1] = (int)round(MNAP_S / 2 + ypos);
		if ((x >= 0 && x <= 20) || x == WIN_W - 1)
			draw_line_ray(info->minimap, (int []){MNAP_S / 2, MNAP_S / 2}, point, \
				BLACK);
		else
			draw_line_ray(info->minimap, (int []){MNAP_S / 2, MNAP_S / 2}, point, \
				RED);
	}
}

void	draw_orthonormal_system_player_centered(t_img *img)
{
	draw_vert_line(img, MNAP_S / 2 - 1, (int []){MNAP_S / 2 - 5, MNAP_S / 2 + \
	5}, BLACK);
	draw_vert_line(img, MNAP_S / 2, (int []){MNAP_S / 2 - 5, MNAP_S / 2 + 5}, \
	BLACK);
	draw_line(img, (int []){MNAP_S / 2 - 5, MNAP_S / 2 - 1}, (int []){MNAP_S / \
	2 + 5, MNAP_S / 2 - 1}, BLACK);
	draw_line(img, (int []){MNAP_S / 2 - 5, MNAP_S / 2}, (int []){MNAP_S / 2 + \
	5, MNAP_S / 2}, BLACK);
}

void	draw_north_symbol_and_borders(t_img *minimap)
{
	const int	size = 12;
	const int	xpos = MNAP_S / 2 - size / 2;
	const int	ypos = 2;
	const int	i = 3;

	draw_rect(minimap, (int []){xpos, ypos}, (int []){size, size}, YELLOW);
	draw_vert_line(minimap, xpos + i, (int []){ypos, ypos + size}, BLACK);
	draw_vert_line(minimap, xpos + size - i, (int []){ypos, ypos + size}, \
	BLACK);
	draw_line(minimap, (int []){xpos + i, ypos}, (int []){xpos + size - i, \
	ypos + size}, BLACK);
	draw_border(minimap, (int []){0, 0}, (int []){191, 191}, BLUE);
	draw_border(minimap, (int []){1, 1}, (int []){190, 190}, BLUE);
}

void	draw_minimap(t_info *info)
{
	int			x;
	int			y;
	double		mapx;
	double		mapy;
	const int	clr[3] = {WHITE, GREY, BLACK};

	draw_rect(info->minimap, (int []){0, 0}, (int []){191, 191}, BLACK);
	x = -1;
	while (++x < MNAP_S - 1)
	{
		y = -1;
		while (++y < MNAP_S - 1)
		{
			mapx = x - (MNAP_S / 2 - info->posx * MNAP_TS);
			mapy = y - (MNAP_S / 2 - info->posy * MNAP_TS);
			if (mapx > 0 && mapx / MNAP_TS < info->mw && mapy > 0 && \
				mapy / MNAP_TS < info->mh)
				pixel_w(info->minimap, x, y, clr[info->map[(int)floor(mapy) \
					/ MNAP_TS][(int)floor(mapx) / MNAP_TS] - 48]);
		}
	}
	draw_cone_raycast(info);
	draw_orthonormal_system_player_centered(info->minimap);
	draw_north_symbol_and_borders(info->minimap);
	mlx_put_image_to_window(info->ptr, info->win, info->minimap->ptr, 20, 20);
}
