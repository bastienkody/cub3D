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

/*	192x192 screen on win at 20,20, ppos centered
	- draw black bg
	- draw floor rect (16x16)
	- draw player icon (1/3 de rect)
	- draw blue border (double lined)
	- mlx_put_img_to_win
*/

void draw_cone_raycast(t_info *info)
{
	t_raycast	rc;
	int			x;
	double		camerax;

	ft_bzero(&rc, sizeof(t_raycast));
	x = -1;
	while (++x < WIN_H)
	{
		camerax = 2 * x / (double)WIN_W - 1;
		rc.mapx = (int)info->posx;
		rc.mapy = (int)info->posy;
		rc.raydirx = info->dirx + info->planex * camerax;
		rc.raydiry = info->diry + info->planey * camerax;
		dda_prep(&rc, info->posx, info->posy);
		dda(&rc, info->map);
		if (rc.side == 0)
			rc.pwall = rc.sidex - rc.deltax;
		else
			rc.pwall = rc.sidey - rc.deltay;
		if (!rc.pwall)
			rc.pwall = 1;
		int a[2] = {96, 96};
		double xpos =(rc.raydirx * (rc.pwall) * MNAP_TS);
		double ypos = (rc.raydiry * (rc.pwall) * MNAP_TS);
		int b[2] =  {a[0] + (int)floor(xpos), a[1] + (int)floor(ypos)};
		if (b[0] > 191)
			b[0] = 191; 
		if (b[0] < 0)
			b[0] = 0;
		if (b[1] > 191)
			b[1] = 191;
		if (b[1] < 0)
			b[1] = 0;
		draw_line(info->minimap, a, b, RED);
	}
}

void draw_north_symbol_and_borders(t_img *minimap)
{
	const int size = 12;
	const int xpos = MNAP_W / 2 - size / 2;
	const int ypos = 2;
	const int i = 3;

	draw_rect(minimap, (int[]){xpos, ypos}, (int[]){size, size}, YELLOW);
	draw_vert_line(minimap, xpos + i, (int[]){ypos, ypos + size}, BLACK);
	draw_vert_line(minimap, xpos + size - i, (int[]){ypos, ypos + size},
				   BLACK);
	draw_line(minimap, (int[]){xpos + i, ypos}, (int[]){xpos + size - i, ypos + size}, BLACK);
	draw_border(minimap, (int[]){0, 0}, (int[]){191, 191}, BLUE);
	draw_border(minimap, (int[]){0, 0}, (int[]){190, 190}, BLUE);
}

void draw_minimap(t_info *info)
{
	int x;
	int y;
	int mapx;
	int mapy;
	const int clr[3] = {WHITE, GREY, BLACK};

	draw_rect(info->minimap, (int[]){0, 0}, (int[]){191, 191}, BLACK);
	x = -1;
	while (++x * MNAP_TS < MNAP_W - 1)
	{
		y = -1;
		while (++y * MNAP_TS < MNAP_H - 1)
		{
			mapx = x - (6 - info->posx);
			mapy = y - (6  - info->posy);
			if (mapx > -1 && mapx < info->mw && mapy > -1 && mapy < info->mh)
				if (x * MNAP_TS - 8 > 0 && y * MNAP_TS - 8 > 0)
					draw_rect(info->minimap, (int[]){x * MNAP_TS - 8, y * MNAP_TS - 8},
						(int[]){MNAP_TS, MNAP_TS}, clr[info->map[mapy][mapx] - 48]);
		}
	}
	//draw_rect(info->minimap, (int[]){5 * MNAP_TS + MNAP_TS / 3, 5 * MNAP_TS + MNAP_TS / 3}, (int[]){MNAP_TS / 3, MNAP_TS / 3}, RED);
	draw_north_symbol_and_borders(info->minimap);
	//draw_vert_line(info->minimap, 96, (int []){0, 191}, RED);
	//draw_line(info->minimap, (int []){0, 96}, (int []){191, 96}, RED);
	draw_cone_raycast(info);
	mlx_put_image_to_window(info->ptr, info->win, info->minimap->ptr, 20, 20);
}
