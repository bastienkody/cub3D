/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:18:39 by bguillau          #+#    #+#             */
/*   Updated: 2023/10/13 16:22:14 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*	includes	*/
# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

/*	alpha const	*/
# define ALLOC_FAIL "Malloc error - cub3D exiting"
# define BAD_ARG_NB "Bad number of argument"
# define BAD_CONFIG_NAME "Bad config file name (*.cub expected)"
# define BAD_LINE "Following line format is not acceptable: "

/*	num const	*/

/*	typedef	*/
typedef struct s_data
{
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	unsigned char	floor_rgb[3];
	unsigned char	ceil_rgb[3];
	char			**map;
}				t_data;

/*	parsing	*/
t_data	*main_parser(int argc, char **argv);

/*	error	*/
void	print_error(char *str);

#endif
