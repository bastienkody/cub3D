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

int	close_window(t_info *info)
{
	end_free(info);
	return (1);
}

void	stop_intro(t_info *info)
{
	info->bg_default = create_image(info->ptr, WIN_W, WIN_H);
	info->is_intro = false;
	line_w(info->bg_default, (int []){0, 0}, (int []){WIN_W, WIN_H}, WHITE);
	mlx_put_image_to_window(info->ptr, info->win, info->bg_default->ptr, 0, 0);
}

int	key_inputs(int keycode, t_info *info)
{
	ft_fprintf(1, "keycode:%i %s\n", keycode, TRUC);
	if (info->is_intro)
		if (keycode == 65293)
			stop_intro(info);
	if (keycode == XK_Escape)
		close_window(info);
	else if (keycode == XK_i)
		print_info(info);
	return (1);
}

int	disp_intro(t_info *info)
{
	static int	counter = 0;
	static int	flag = -1;

	if (!info->is_intro)
		return (1);
	counter++;
	if (counter > INTRO_COUNTER_UBU)
	{
		counter = 0;
		flag *= -1;
	}
	if (flag < 0)
		mlx_put_image_to_window(info->ptr, info->win, info->intro1->ptr, 0, 0);
	else
		mlx_put_image_to_window(info->ptr, info->win, info->intro2->ptr, 0, 0);
	return (0);
}
