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

/*	if mouse has moved : outro redraw	*/
int	outro_update(t_info *info)
{
	static int	prev_out_x = 0;
	static int	prev_out_y = 0;
	static int	x_out = -1;
	static int	y_out = -1;

	mlx_mouse_get_pos(info->ptr, info->win, &x_out, &y_out);
	if (info->is_outro && (x_out != prev_out_x || y_out != prev_out_y))
	{
		prev_out_x = x_out;
		prev_out_y = y_out;
		return (outro(info, x_out, y_out));
	}
	return (0);
}

/*	RESUME vs QUIT buttons positions :
	see cub3D.h defines
	-> RESUME pos = X, Y, with size X_S, Y_S
	-> QUIT pos = resume + y offset
*/
int	outro(t_info *info, int x, int y)
{
	if (info->is_outro == false)
	{
		mlx_put_image_to_window(info->ptr, info->win, info->bg_default->ptr, \
		0, 0);
		draw_minimap(info);
		if (info->is_maximap)
		{
			info->is_maximap = false;
			return (maximap_display(info), 1);
		}
	}
	if (x >= X && x <= X_S && y >= Y && y <= Y_S)
		mlx_put_image_to_window(info->ptr, info->win, info->outro[1]->ptr, \
		0, 0);
	else if (x >= X && x <= X_S && y >= Y + Y_OFST && y <= Y_S + Y_OFST)
		mlx_put_image_to_window(info->ptr, info->win, info->outro[2]->ptr, \
		0, 0);
	else
		mlx_put_image_to_window(info->ptr, info->win, info->outro[0]->ptr, \
		0, 0);
	return (1);
}

int	outro_mouse_inputs(int but, int x, int y, t_info *info)
{
	if (but != 1)
		return (0);
	if (x >= X && x <= X_S && y >= Y && y <= Y_S)
	{
		info->is_outro = false;
		mlx_put_image_to_window(info->ptr, info->win, info->bg_default->ptr, \
		0, 0);
		draw_minimap(info);
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
