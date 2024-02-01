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
	return (1);
}

int	is_move_cmds(int keycode)
{
	return ((keycode == XK_w || keycode == XK_a || keycode == XK_s || \
			keycode == XK_d) || (keycode == XK_Right || keycode == XK_Left));
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
			return (info->is_intro = false, raycast_launcher(info), draw_minimap(info), 1);
		else if (keycode == XK_Escape)
			end_free(info);
	}
	else if (keycode == XK_Escape)
		return (info->is_outro = !info->is_outro, 1);
	else if (keycode == XK_m)
		info->is_maximap = !info->is_maximap;
	else if (keycode == XK_r)
	{
		raycast_launcher(info);
		draw_minimap(info);
	}
	else if (is_move_cmds(keycode) && !info->is_maximap && !info->is_outro)
		key_movement(keycode, info);
	else if (keycode == XK_c && !info->is_maximap && !info->is_outro)
		crouch_uncrouch(info);
	return (1);
}
