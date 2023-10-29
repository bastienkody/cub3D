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

void	end_free(t_info *info)
{
	if (info && info->map)
		free_charray(info->map);
	if (info)
		free(info);
}

int	main(int argc, char **argv, __attribute__((unused)) char **envp)
{
	t_info	*info;

	(void)argc;
	(void)argv;
	info = calloc(1, sizeof(t_info));
	//info = main_parser(argc, argv);
	//if (!info || !map_checker(info))
		//return (1);
	//print_info(info);
	init_display(info);
	mlx_loop(info->ptr);
	return (end_free(info), 0);
}
