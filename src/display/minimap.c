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

/*	
	fminimap is an image of the full map
	minimap : fminimap rounded to 200x200 with player centered !
*/

void	draw_f_minimap(t_info *info, int *oldx, int *oldy)
{
	int			y;
	int			x;
	const int	psize = MNAP_TS / 2;
	const int	colorz[3] = {WHITE, GREY, BLACK}; 

	y = -1;
	while (++y > -1 && info->map[y] != NULL)
	{
		x = -1;
		while (++x > -1 && info->map[y][x] != '\0')
		{
			draw_rect_w_border(info->fminimap, (int []){x * MNAP_TS, y * \
			MNAP_TS}, (int []){MNAP_TS, MNAP_TS}, colorz[info->map[y][x] - '0']);
		}
	}
	draw_rect(info->fminimap, (int []){info->pposx * MNAP_TS + psize / 2, \
	info->pposy * MNAP_TS + psize / 2}, (int []){psize, psize}, RED);
	*oldx = info->pposx;
	*oldy = info->pposy;
	//mlx_put_image_to_window(info->ptr, info->win, info->fminimap->ptr, 0, 0);
}

/*	fetch 200x200 of fminimap with ppos centered*/
void	draw_minimap(__attribute__((unused)) t_info *info)
{
	static int	oldx = -1;
	static int	oldy = -1;
	//const int	x = info->pposx * MNAP_TS - MNAP_TS / 2;
	//const int	y = info->pposy * MNAP_TS - MNAP_TS / 2;

	if (info->pposx != oldx || info->pposy != oldy)
		draw_f_minimap(info, &oldx, &oldy);
	draw_rect(info->minimap, (int []){0, 0}, (int []){199,199}, BLACK);
	img_to_img(info->fminimap, info->minimap, (int []){0,0}, (int []){200, 200});
	draw_border(info->minimap, (int []){0, 0}, (int []){199,199}, BLUE);
	mlx_put_image_to_window(info->ptr, info->win, info->minimap->ptr, 20, 20);
}

