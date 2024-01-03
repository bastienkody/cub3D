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

int	mouse_inputs(int button, int x, int y, t_info *info)
{
	if (info->is_maximap)
		maximap_teleport(button, x, y, info);
	if (info->is_outro)
		outro_mouse_inputs(button, x, y, info);
	return (1);
}

int	is_input_key_cmds(int keycode)
{
	return ((keycode == XK_w || keycode == XK_a || keycode == XK_s || \
			keycode == XK_d || keycode == XK_Right || keycode == XK_Left));
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
			return (info->is_intro = false, 1);
		else if (keycode == XK_Escape)
			end_free(info);
	}
	else if (keycode == XK_Escape)
		return (info->is_outro = !info->is_outro, 1);
	else if (!info->is_intro && keycode == XK_m)
		maximap_display(info);
	else if (is_input_key_cmds(keycode) && info->is_maximap)
		maximap_key_movement(keycode, info);
	return (1);
}
