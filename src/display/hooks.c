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

	// disp une win qui propose de quitter
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

int	mouse_inputs(int button, int x, int y, t_info *info)
{
	if (info->is_maximap)
		maximap_teleport(button, x, y, info);
	return (1);
}

int	key_inputs(int keycode, t_info *info)
{
	if (info->is_intro)
		if (keycode == 65293)
			stop_intro(info);
	if (keycode == XK_Escape)
		close_window(info);
	else if (keycode == XK_i)
		print_info(info);
	else if (keycode == XK_m && !info->is_intro)
		maximap_display(info);
	return (1);
}

int	disp_intro(t_info *info)
{
	static int	counter = 0;

	if (!info->is_intro)
		return (1);
	counter++;
	if (counter > INTRO_COUNTER)
		counter = 0;
	if (counter <= INTRO_COUNTER / 2)
		mlx_put_image_to_window(info->ptr, info->win, info->intro1->ptr, 0, 0);
	else
		mlx_put_image_to_window(info->ptr, info->win, info->intro2->ptr, 0, 0);
	return (0);
}
