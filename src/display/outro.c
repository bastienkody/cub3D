/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:25:16 by bguillau          #+#    #+#             */
/*   Updated: 2023/12/29 13:25:19 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/*	RESUME vs QUIT buttons positions :
	see cub3D.h defines
	-> RESUME pos = X, Y, with size X_S, Y_S
	-> QUIT pos = resume + y offset
*/

int	outro(t_info *info)
{
	static int	old_x = 0;
	static int	old_y = 0;
	int			x;
	int 		y;

	info->is_outro = !info->is_outro;
	x = -1;
	y = -1;
	mlx_mouse_get_pos(info->ptr, info->win, &x, &y);
	if (x != old_x || y != old_y)
	{
		if (x >= X && x <= X_S && y >= Y && y <= Y_S)
			mlx_put_image_to_window(info->ptr, info->win, info->outro[1]->ptr, 0, 0);
		else if (x >= X && x <= X_S && y >= Y + Y_OFST && y <= Y_S + Y_OFST)
			mlx_put_image_to_window(info->ptr, info->win, info->outro[2]->ptr, 0, 0);
		else
			mlx_put_image_to_window(info->ptr, info->win, info->outro[0]->ptr, 0, 0);
	}
	old_x = x;
	old_y = y;
	return (1);
}

int	outro_key_inputs(int keycode, t_info *info)
{
	if (keycode == 65293 || keycode == XK_q)
		end_free(info);
	if (keycode == XK_Escape)
	{
		info->is_outro = false;
		mlx_put_image_to_window(info->ptr, info->win, info->bg_default->ptr, 0, 0);
		if (info->is_maximap)
		{
			info->is_maximap = false;
			return (maximap_display(info), 1);
		}
	}
	return (1);
}

int	outro_mouse_inputs(int but, int x, int y, t_info *info)
{
	if (but != 1)
		return (0);
	if (x >= X && x <= X_S && y >= Y && y <= Y_S)
	{
		info->is_outro = false;
		mlx_put_image_to_window(info->ptr, info->win, info->bg_default->ptr, 0, 0);
		if (info->is_maximap)
		{
			info->is_maximap = false;
			return (maximap_display(info), 1);
		}
	}
	else if (x >= X && x <= X_S && y >= Y + Y_OFST && y <= Y_S + Y_OFST)
		return (end_free(info), 1);
	return (0);
}
