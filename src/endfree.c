/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:23:33 by bguillau          #+#    #+#             */
/*   Updated: 2023/10/13 16:25:19 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	unload_texture(void *mlx_ptr, t_img *img)
{
	if (img && img->ptr)
	{
		mlx_destroy_image(mlx_ptr, img->ptr);
		free(img);
	}
}

void	end_parser(t_parser *pars)
{
	if (!pars)
		return ;
	if (pars->map)
		free_charray(pars->map);
	if (pars->no_path)
		free(pars->no_path);
	if (pars->so_path)
		free(pars->so_path);
	if (pars->we_path)
		free(pars->we_path);
	if (pars->ea_path)
		free(pars->ea_path);
}

void	end_free(t_info *info)
{
	if (!info)
		return ;
	if (info->map)
		free_charray(info->map);
	if (info->ptr)
	{
		unload_texture(info->ptr, info->intro1);
		unload_texture(info->ptr, info->intro2);
		unload_texture(info->ptr, info->bg_default);
		unload_texture(info->ptr, info->n_text);
		unload_texture(info->ptr, info->s_text);
		unload_texture(info->ptr, info->w_text);
		unload_texture(info->ptr, info->e_text);
		unload_texture(info->ptr, info->maximap);
		if (info->win)
			mlx_destroy_window(info->ptr, info->win);
		mlx_destroy_display(info->ptr);
		free(info->ptr);
	}
	free(info);
	exit(EXIT_SUCCESS);
}
