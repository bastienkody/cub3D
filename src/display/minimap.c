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

/*	200x200 ppos centered pixel_w on win at 20,20
	- draw black bg
	- draw floor pixel : checks needed (>0 && inside map)
	- draw player icon
	- draw blue border
	- mlxput	*/
void	draw_minimap(t_info *info)
{
	const int	m_h = tab_len(info->map);
	const int	m_w = ft_strlen(*info->map);
	int			x;
	int			y;
	const int	clr[3] = {WHITE, GREY, BLACK};
	int			mapval_x = 0;
	int			mapval_y = 0;
	
	draw_rect(info->minimap, (int []){0, 0}, (int []){199, 199}, BLACK);
	x = 0;
	while (x * MNAP_TS < MNAP_W -1)
	{
		y = 0;
		while (y *MNAP_TS < MNAP_H - 1)
		{
			// pb de signe ? 
			mapval_x = x - (5 - info->pposx);
			mapval_y = y - (5 - info->pposy);
			if (mapval_x > -1 && mapval_x < m_w && mapval_y > -1 && y + mapval_y < m_h)
			{
				//ft_fprintf(1, "new rect in anchor x%i y%i, looking for clr in map y%i x%i\n", x, y, y - info->pposy, x - info->pposx);
				draw_rect_w_border(info->minimap, (int []){x * MNAP_TS, y * MNAP_TS}, (int []) \
				{MNAP_TS, MNAP_TS}, clr[info->map[mapval_y][mapval_x] - 48]);
			}
			y++;
		}
		x++;
	}
	draw_rect(info->minimap, (int []){5 * MNAP_TS + MNAP_TS / 3, 5 * MNAP_TS + MNAP_TS / 3}, (int []){MNAP_TS /3, MNAP_TS /3}, RED);
	//draw_player_icon(info, info->minimap, MNAP_TS);
	draw_border(info->minimap, (int []){0, 0}, (int []){MNAP_W - 1, MNAP_H - 1}, BLUE);
	mlx_put_image_to_window(info->ptr, info->win, info->minimap->ptr, 20, 20);
}

