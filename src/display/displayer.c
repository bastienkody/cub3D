/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displayer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bastienguillaume <marvin@42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 15:41:22 by bastienguilla     #+#    #+#             */
/*   Updated: 2024/01/02 15:41:25 by bastienguilla    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

/*

	I think we might need a info->last_disp_screen to know what was the last
	display (info, outro, maximap or std). This might help us to know if redraw
	is needed. For example for std : if that was the last display and the
	player did not move (wether normal or via maximap), no need to redraw.

	For outro and maximap it is done already inside their own functions. Note
	that they also call what should be displayed when you leave outro or maximap.
	A more generalistic way might be more interesting, especially for 
	std/minimap coverage. All display changes must be done into display_manager.
	
*/

void	disp_intro(t_info *info)
{
	static int	counter = 0;

	if (!info->is_intro)
		return ;
	counter++;
	if (counter > INTRO_COUNTER)
		counter = 0;
	if (counter <= INTRO_COUNTER / 2)
		mlx_put_image_to_window(info->ptr, info->win, info->intro1->ptr, 0, 0);
	else
		mlx_put_image_to_window(info->ptr, info->win, info->intro2->ptr, 0, 0);
}

void	disp_standard(t_info *info)
{
	if (true) // smthg has changed, need to redraw
	{
		//line_w(info->bg_default, (int []){0, 0}, (int []){WIN_W, WIN_H}, WHITE);
		mlx_put_image_to_window(info->ptr, info->win, info->bg_default->ptr, 0, 0);
		draw_minimap(info);
	}
}

/*	lauch by mlx_loop. calls intro at start 
	then redraw outro if mouse moved (mouse check in here)	*/
int	display_manager(t_info *info)
{
	if (info->is_intro)
		return (disp_intro(info), 1);
	if (info->is_outro)
		return (outro_update(info));
	if (!info->is_intro && !info->is_outro && !info->is_maximap)
		disp_standard(info);
	return (0);
}

