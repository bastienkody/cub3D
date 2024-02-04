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

void	draw_north_symbol(t_img *minimap)
{
	const int	size = 12;
	const int	xpos = MNAP_W / 2 - size / 2;
	const int	ypos = 2;
	const int	i = 3;

	draw_rect(minimap, (int[]){xpos, ypos}, (int[]){size, size}, YELLOW);
	draw_vert_line(minimap, xpos + i, (int[]){ypos, ypos + size}, BLACK);
	draw_vert_line(minimap, xpos + size - i, (int[]){ypos, ypos + size}, BLACK);
	draw_line(minimap, (int[]){xpos + i, ypos}, (int[]){xpos + size - i, ypos + size}, BLACK);
}

/*	192x192 screen on win at 20,20, ppos centered
	- draw black bg
	- draw floor rect (16x16)
	- draw player icon (1/3 de rect)
	- draw blue border (double lined)
	- mlx_put_img_to_win
*/

void	draw_minimap(t_info *info)
{
	int			x;
	int			y;
	int			mapx;
	int			mapy;
	const int	clr[3] = {WHITE, GREY, BLACK};

	draw_rect(info->minimap, (int []){0, 0}, (int []){191, 191}, BLACK);
	x = -1;
	while (++x * MNAP_TS < MNAP_W -1)
	{
		y = -1;
		while (++y * MNAP_TS < MNAP_H - 1)
		{
			mapx = x - (5 - info->posx);
			mapy = y - (5 - info->posy);
			if (mapx > -1 && mapx < info->mw && mapy > -1 && mapy < info->mh)
				draw_rect(info->minimap, (int []){x * MNAP_TS, y * MNAP_TS}, \
				(int []){MNAP_TS, MNAP_TS}, clr[info->map[mapy][mapx] - 48]);
		}
	}
	draw_rect(info->minimap, (int []){5 * MNAP_TS + MNAP_TS / 3, 5 * MNAP_TS + \
	MNAP_TS / 3}, (int []){MNAP_TS / 3, MNAP_TS / 3}, RED);
	draw_border(info->minimap, (int []){0, 0}, (int []){191, 191}, BLUE);
	draw_border(info->minimap, (int []){0, 0}, (int []){190, 190}, BLUE);
	draw_north_symbol(info->minimap);
	mlx_put_image_to_window(info->ptr, info->win, info->minimap->ptr, 20, 20);
}
