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

void	draw_f_minimap(t_info *info)
{
	int			y;
	int			x;
	// IN BLUE FOR DEBUG : const int	colorz[3] = {WHITE, GREY, BLACK}; colorz[(int)info->map[y][x] - '0']

	y = -1;
	while (++y > -1 && info->map[y] != NULL)
	{
		x = -1;
		while (++x > -1 && info->map[y][x] != '\0')
		{
			draw_rect_w_border(info->fminimap, (int []){x * MNAP_TS, y * \
			MNAP_TS}, (int []){MNAP_TS, MNAP_TS}, BLUE);
		}
	}
	draw_rect(info->fminimap, (int []){info->pposx * MNAP_TS / 2, \
	info->pposy * MNAP_TS / 2}, (int []){MNAP_TS / 2, MNAP_TS / 2}, RED);
	mlx_put_image_to_window(info->ptr, info->win, info->fminimap->ptr, 0, 0);
}

/*	fetch 200x200 of fminimap with ppos centered*/
void	draw_minimap(__attribute__((unused)) t_info *info)
{
	draw_f_minimap(info);
	//pixel_w(info->fminimap, 0, 0, BLUE); // with this it works nice
	ft_fprintf(1, "color 0, 0 bgdef : %x\n", get_color(info->fminimap, 2, 0));
	//img_to_img(info->fminimap, info->minimap, (int []){0,0}, (int []){200, 200});
	//mlx_put_image_to_window(info->ptr, info->win, info->minimap->ptr, 20, 20);
}

