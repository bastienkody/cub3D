/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 16:53:19 by bguillau          #+#    #+#             */
/*   Updated: 2023/11/17 16:39:33 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

void	load_textures(t_info *info, t_parser *pars)
{
	info->intro1 = create_xpm_image(info->ptr, \
		"map/textures/intrologo/logo_pink_green_0.xpm");
	info->intro2 = create_xpm_image(info->ptr, \
		"map/textures/intrologo/logo_pink_green_1.xpm");
	info->outro[0] = create_xpm_image(info->ptr, "map/textures/outro/outro3.\
xpm");
	info->outro[1] = create_xpm_image(info->ptr, "map/textures/outro/outro3_r.\
xpm");
	info->outro[2] = create_xpm_image(info->ptr, "map/textures/outro/outro3_q.\
xpm");
	info->n_text = create_xpm_image(info->ptr, pars->no_path);
	printf("north ok\n");
	info->s_text = create_xpm_image(info->ptr, pars->so_path);
	printf("south ok\n");
	info->w_text = create_xpm_image(info->ptr, pars->we_path);
	printf("west ok\n");
	info->e_text = create_xpm_image(info->ptr, pars->ea_path);
	printf("east ok\n");
	info->bg_default = create_image(info->ptr, WIN_W, WIN_H);
	info->maximap = create_image(info->ptr, WIN_W, WIN_H);
	info->minimap = create_image(info->ptr, MNAP_S, MNAP_S);
	info->rc = create_image(info->ptr, WIN_W, WIN_H);
}

int	check_textures_load(t_info *info)
{
	if (!info->intro1 || !info->intro1->ptr || !info->intro2 || \
		!info->outro[0] \
		|| !info->outro[0]->ptr || !info->outro[1] || !info->outro[1]->ptr || \
		!info->outro[2] || !info->outro[2]->ptr ||!info->intro2->ptr || \
		!info->n_text || !info->n_text->ptr || !info->s_text || \
		!info->s_text->ptr || !info->w_text || !info->w_text->ptr || \
		!info->e_text || !info->e_text->ptr || !info->minimap || \
		!info->minimap->ptr || !info->maximap || !info->maximap->ptr || \
		!info->rc || !info->rc->ptr)
		return (0);
	return (1);
}

int	init_display(t_info *info, t_parser *pars)
{
	info->ptr = mlx_init();
	if (!info->ptr)
		return (print_error(BAD_INI, NULL), 0);
	info->win = mlx_new_window(info->ptr, WIN_W, WIN_H, "Cub3D");
	if (!info->win)
		return (print_error(BAD_WIN, NULL), 0);
	info->is_intro = true;
	load_textures(info, pars);
	if (!check_textures_load(info))
		return (0);
	draw_first_maximap(info);
	return (1);
}
