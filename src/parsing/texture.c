/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillau <bguillau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 13:27:40 by bguillau          #+#    #+#             */
/*   Updated: 2023/12/29 13:27:42 by bguillau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3D.h"

int	store_texture(char *path, char *id, t_parser *pars)
{
	if (!path)
		return (print_error(ALLOC_FAIL, NULL), 0);
	if ((!ft_strcmp(id, "NO") && pars->no_path) || (!ft_strcmp(id, "SO") && \
		pars->so_path) || (!ft_strcmp(id, "WE") && pars->we_path) || \
		(!ft_strcmp(id, "EA") && pars->ea_path))
		return (print_error(MULTI_DEF, id), free(path), 0);
	if (!ft_strcmp(id, "NO") && !pars->no_path)
		pars->no_path = path;
	else if (!ft_strcmp(id, "SO") && !pars->so_path)
		pars->so_path = path;
	else if (!ft_strcmp(id, "WE") && !pars->we_path)
		pars->we_path = path;
	else if (!ft_strcmp(id, "EA") && !pars->ea_path)
		pars->ea_path = path;
	return (1);
}

char	*rm_peer_quotes(char *str)
{
	char	*new;
	int		i;

	if ((*str == '\'' || *str == '\"') && *str == str[ft_strlen(str) - 1])
	{
		new = malloc(sizeof(char *) * (ft_strlen(str) - 2 + 1));
		if (!new)
			return (NULL);
		i = 0;
		while (++i < (int)ft_strlen(str) - 1)
			new[i - 1] = str[i];
		new[i - 1] = '\0';
	}
	else
		new = ft_strdup(str);
	return (new);
}

/*	filename bc mlx ptr not yet generated but needed for xpm_to_img	*/
int	get_texture(char *line, char **split, t_parser *pars)
{
	int		fd;
	char	*path;

	if (tab_len(split) != 2)
		return (print_error(BADLINE, line), free_charray(split), free(line), 0);
	path = rm_peer_quotes(split[1]);
	if (!path)
		return (print_error(ALLOC_FAIL, 0), free_charray(split), free(line), 0);
	if (ft_strlen(path) < 5 || ft_strcmp(&path[ft_strlen(path) -4], ".xpm"))
		return (print_error(BAD_XPM, path), free_charray(split), free(line), \
			free(path), 0);
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(2, "Error\nImpossible to open texture path ");
		perror(path);
		return (free_charray(split), free(line), free(path), fd);
	}
	close(fd);
	fd = store_texture(path, split[0], pars);
	return (free_charray(split), free(line), fd);
}
