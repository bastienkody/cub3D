/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maburnet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:37:54 by bguillau          #+#    #+#             */
/*   Updated: 2024/01/29 16:15:04 by maburnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	mouse_inputs(int button, int x, int y, t_info *info)
{
	if (info->is_maximap && !info->is_outro)
		maximap_teleport(button, x, y, info);
	if (info->is_outro)
		outro_mouse_inputs(button, x, y, info);
	if (!info->is_intro && !info->is_outro && !info->is_maximap)
		game_mouse_inputs(button, info);
	return (1);
}

int	key_release(int keycode, t_info *info)
{
	static const int	keys[7] = {XK_w, XK_s, XK_a, XK_d, XK_Left, XK_Right, \
	XK_Shift_L};
	int					i;

	i = -1;
	while (++i < 7)
		if (keycode == keys[i])
			return (info->keys[i] = false, 1);
	return (0);
}

int	key_press(int keycode, t_info *info)
{
	static const int	keys[7] = {XK_w, XK_s, XK_a, XK_d, XK_Left, XK_Right, \
	XK_Shift_L};
	int					i;

	i = -1;
	while (++i < 7 && !info->is_intro && !info->is_maximap && !info->is_outro)
		if (keycode == keys[i])
			return (info->keys[i] = true, 1);
	key_inputs(keycode, info);
	return (0);
}

int	key_inputs(int keycode, t_info *info)
{
	if (keycode == XK_i)
		print_info(info);
	else if (keycode == XK_q)
		end_free(info);
	else if (info->is_intro)
	{
		if (keycode == 65293)
			return (info->is_intro = false, raycast_launcher(info));
		else if (keycode == XK_Escape)
			end_free(info);
	}
	else if (keycode == XK_Escape)
		return (info->is_outro = !info->is_outro, raycast_launcher(info));
	else if (keycode == XK_m && !info->is_outro && info->mmap_tile_s > 3)
		return (info->is_maximap = !info->is_maximap, raycast_launcher(info));
	else if (keycode == XK_r && !info->is_maximap && !info->is_outro)
		raycast_launcher(info);
	return (1);
}
