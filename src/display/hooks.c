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
	if (info->is_outro)
		outro_mouse_inputs(button, x, y, info);
	return (1);
}

int	is_input_key_cmds(int keycode)
{
	return ((keycode == XK_w || keycode == XK_a || keycode == XK_s || \
	keycode == XK_d || keycode == XK_Up || keycode == XK_Left || \
	keycode == XK_Down || keycode == XK_Right ));
}

/*	
	- launch game with enter (esc or q directly leaves during intro)
	- get exit window with escape : 
		-> click resume or press esc to resume
		-> click quit or press enter or q to quit
	- exits directly with red cross or via pressing q, fro; anywhere
*/
int	key_inputs(int keycode, t_info *info)
{
	if (info->is_intro)
	{
		if (keycode == 65293)
			stop_intro(info);
		else if (keycode == XK_Escape || keycode == XK_q)
			end_free(info);
	}
	if (info->is_outro)
		return (outro_key_inputs(keycode, info), 1);
	if (!info->is_intro && (keycode == XK_Escape))
		outro(info);
	else if (!info->is_intro && keycode == XK_m)
		maximap_display(info);
	else if (keycode == XK_q)
		end_free(info);
	else if (keycode == XK_i)
		print_info(info);
	else if (is_input_key_cmds(keycode) && info->is_maximap)
		maximap_key_movement(keycode, info);	
	return (1);
}

int	disp_intro(t_info *info)
{
	static int	counter = 0;

	if (info->is_outro)
	{
		info->is_outro = !info->is_outro;
		return (outro(info), 1);
	}	
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
