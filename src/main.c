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

void	end_free(t_data *data)
{
	if (data && data->map)
		free_charray(data->map);
	if (data)
		free(data);
}

int	main(int argc, char ** argv, __attribute__((unused)) char **envp)
{
	t_data	*data;

	data = main_parser(argc, argv);
	if (!data)
		return (2);
	print_data(data);
	return (end_free(data), 0);
}
