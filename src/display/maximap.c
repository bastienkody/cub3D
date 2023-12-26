/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:37:54 by bguillau          #+#    #+#             */
/*   Updated: 2023/11/17 16:37:55 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

// wall : black 1
// floor : white 0
// space : grey  2


/*	need to be upgrading : 
		with precise angle
		x vs y intensity to choose S vs W for if diagonale dir
		Resize pour whole map fits within screen
*/
void	draw_player_icon(t_info *info, int size)
{
	t_img		*choosen;
	const int	xpos = info->pposx * size;
	const int	ypos = info->pposy * size;

	choosen = info->player[0];
	if (info->pdiry == -1)
		choosen = info->player[1];
	else if (info->pdirx == -1)
		choosen = info->player[2];
	else if (info->pdirx == 1)
		choosen = info->player[3];
	ft_fprintf(2, "about to draw player in x:%i, y:%i\n", xpos, ypos);
	mlx_put_image_to_window(info->ptr, info->win, choosen->ptr, xpos, ypos);
}

void	maximap_display(t_info *info)
{
	int			y;
	int			x;
	const int	colorz[3] = {WHITE, GREY, BLACK};

	if (info->is_intro)
		return ;
	info->is_maximap = !info->is_maximap;
	if (!info->is_maximap)
		return ((void)mlx_put_image_to_window(info->ptr, info->win, \
		info->bg_default->ptr, 0, 0));
	y = -1;
	while (++y * TILE_S < WIN_H && info->map[y] != NULL)
	{
		x = -1;
		while (++x * TILE_S < WIN_W && info->map[y][x] != '\0')
		{
			draw_rect(info->maximap, (int []){x * TILE_S, y * TILE_S}, \
			(int []){TILE_S, TILE_S}, \
			colorz[(int)info->map[y][x] - '0']);
			ft_fprintf(1, "maxirect in x=%i, y=%i, colorz=%i\n", x, y, colorz[(int)info->map[y][x] - '0']);
		}
	}
	mlx_put_image_to_window(info->ptr, info->win, info->maximap->ptr, 0, 0);
	draw_player_icon(info, 64);
}
