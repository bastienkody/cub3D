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

// checkmap + allocinfo + initdisplay (ptr, xpmload)
t_info	*pars_to_info(t_parser *pars)
{
	t_info	*info;

	if (!map_checker(pars))
		return (NULL);
	info = calloc(1, sizeof(t_info));
	if (!info)
		return (print_error(ALLOC_FAIL, NULL), NULL);
	info->posx = pars->pposx;
	info->posy = pars->pposy;
	info->dirx = pars->pdirx;
	info->diry = pars->pdiry;
	info->planex = pars->planex;
	info->planey = pars->planey;
	info->floor = pars->floor_rgb;
	info->ceil = pars->ceil_rgb;
	info->map = pars->map;
	info->mh = tab_len(info->map);
	info->mw = ft_strlen(*info->map);
	pars->map = NULL;
	if (!init_display(info, pars))
		return (NULL);
	return (end_parser(pars), info);
}

void	run(t_info *info)
{
	mlx_mouse_hook(info->win, &mouse_inputs, info);
	mlx_hook(info->win, 2, 1L << 0, &key_inputs, info);
	mlx_hook(info->win, 17, 0, &end_free, info);
	mlx_loop_hook(info->ptr, &display_manager, info);
	mlx_loop(info->ptr);
}

int	main(int argc, char **argv, __attribute__((unused)) char **envp)
{
	t_parser	*pars;	
	t_info		*info;

	pars = main_parser(argc, argv); // fetch config file
	if (!pars)
		return (1);
	info = pars_to_info(pars);
	if (!info)
		return (end_parser(pars), end_free(info), 1);
	run(info);
	return (end_free(info), 0);
}
