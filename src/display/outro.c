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

/*	display an outro window with two rects : go back to game or quit
	press excape to go back to game
	press Enter to ocnfirm leave
	if outro call from maximap
*/
int	outro(t_info *info)
{
	info->is_outro = !info->is_outro;
	mlx_put_image_to_window(info->ptr, info->win, info->outro->ptr, 0, 0);
	return (1);
}

int	outro_key_inputs(int keycode, t_info *info)
{
	if (keycode == 65293)
		end_free(info);
	if (keycode == XK_Escape)
	{
		info->is_outro = false;
		mlx_put_image_to_window(info->ptr, info->win, info->bg_default->ptr, 0, 0);
		if (info->is_maximap)
		{
			info->is_maximap = false;
			return (maximap_display(info), 1);
		}
	}
	return (1);
}
