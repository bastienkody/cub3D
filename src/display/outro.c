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
int	outro_update(int x, int y)
{
	static int	prev_out_x = -1;
	static int	prev_out_y = -1;

	if (x != prev_out_x || y != prev_out_y)
	{
		prev_out_x = x;
		prev_out_y = y;
		return (1);
	}
	return (0);
}

/*	RESUME vs QUIT buttons positions :
	see cub3D.h defines
	-> RESUME pos = X, Y, with size X_S, Y_S
	-> QUIT pos = resume + y offset
*/
int	outro(t_info *info)
{
	static int	x;
	static int	y;

	mlx_mouse_get_pos(info->ptr, info->win, &x, &y);
	if (info->p_scene == OUTRO && !outro_update(x, y))
		return (ft_fprintf(1, "no redraw outro needed\n"));
	if (info->is_outro == false)
		return (info->p_scene = STD, 1);
	if (x >= X && x <= X_S && y >= Y && y <= Y_S)
		mlx_put_image_to_window(info->ptr, info->win, info->outro[1]->ptr, \
		0, 0);
	else if (x >= X && x <= X_S && y >= Y + Y_OFST && y <= Y_S + Y_OFST)
		mlx_put_image_to_window(info->ptr, info->win, info->outro[2]->ptr, \
		0, 0);
	else
		mlx_put_image_to_window(info->ptr, info->win, info->outro[0]->ptr, \
		0, 0);
	return (info->p_scene = OUTRO, 1);
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
