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
# define LINE_NOT_CONFIG "Texture/rgb config is not completed yet but the \
	following line does not comply with config format: "

/*	num const	*/

/*	typedef	*/
typedef struct s_data
{
	int				*no_path;
	int				*so_path;
	int				*we_path;
	int				*ea_path;
	unsigned char	floor_rgb[3];
	unsigned char	ceil_rgb[3];
	char			**map;
}				t_data;

/*	parsing	*/
t_data	*main_parser(int argc, char **argv);
int		get_texture(char *line, char **split, t_data *data);
int		get_rgb(char *line, char **split, t_data *data);

/*	parsing utils	*/
int		tab_len(char **tab);
int		is_str_only_c(char *str, char c);
int		is_texture_line(char **split);
int		is_rgb_line(char **split);
void	update_map_on(int *map_on, t_data *data);

/*	error	*/
void	print_error(char *str1, char *str2);

#endif
