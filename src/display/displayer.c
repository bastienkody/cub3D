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

/*	search for any move key being pressed and call key_movement with keycode	*/
void	moves_standard(t_info *info)
{
	static const int	keys[6] = {XK_w, XK_s, XK_a, XK_d, XK_Left, XK_Right};
	int	i;

	i = -1;
	while(++i < 6)
	{
		if (info->keys[i])
			key_movement(keys[i], info);
	}
}

/*	lauch by mlx_loop. calls intro at start 
	then redraw outro if mouse moved (mouse check in here)	
	new: look for keys pressed and call movements accordingly	*/
int	loop_manager(t_info *info)
{
	if (info->is_intro)
		return (disp_intro(info), 1);
	if (info->is_outro)
		return (outro(info), 1);
	if (info->is_maximap)
		return (maximap_display(info), 1);
	if (!info->is_intro && !info->is_outro && !info->is_maximap)
		return (moves_standard(info), 1);
	return (0);
}

