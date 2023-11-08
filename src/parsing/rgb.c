#include "../../inc/cub3D.h"

/*	protected against redefinition of colors	*/
int	store_rgb(t_info *info, char **line_split, unsigned char rgb_tmp[3])
{
	if (*line_split[0] == 'F' && !info->floor)
	{
		info->floor_rgb = argb_hex(255, rgb_tmp[0], rgb_tmp[1], rgb_tmp[2]);
		info->floor = true;
		ft_fprintf(1, "Floor color : ");
		ft_fprintf(1, "%x\n", info->floor_rgb);
	}
	else if (*line_split[0] == 'F' && info->floor)
		return (print_error(MULTI_DEF, line_split[0]), 0);
	if (*line_split[0] == 'C' && !info->ceil)
	{
		info->ceil_rgb = argb_hex(255, rgb_tmp[0], rgb_tmp[1], rgb_tmp[2]);
		info->ceil = true;
		ft_fprintf(1, "Ceiling color : ");
		ft_fprintf(1, "%x\n", info->ceil_rgb);
	}
	else if (*line_split[0] == 'C' && !info->ceil)
		return (print_error(MULTI_DEF, line_split[0]), 0);
	return (1);
}

int	check_rgb(t_info *info, char **rgb_split, char *line, char **line_split)
{
	int				i;
	int				j;
	unsigned char	rgb_tmp[3];

	if (!rgb_split)
		return (print_error(ALLOC_FAIL, NULL), 0);
	if (count_c_in_str(line, ',') != 2 || tab_len(rgb_split) != 3)
		return (print_error(BADLINE, line), free_charray(rgb_split), 0);
	i = -1;
	while (++i < 3)
	{
		if (!ft_atouc_novf(rgb_split[i], &rgb_tmp[i]))
			return (print_error(BAD_NBR, line), free_charray(rgb_split), 0);
		j = -1;
		while (++j < 3 && rgb_split[i][j])
			if (!ft_isdigit(rgb_split[i][j]))
				return (print_error(BAD_NBR, line), free_charray(rgb_split), 0);
	}
	if (!store_rgb(info, line_split, rgb_tmp))
		return (free_charray(rgb_split), 0);
	return (1);
}

int	get_rgb(char *line, char **split, t_info *info)
{
	char		*join;
	char		**rgb_split;

	if (tab_len(split) < 2)
		return (print_error(BADLINE, line), free_charray(split), free(line), 0);
	join = superjoin_tab_fall(split + 1);
	if (!join)
		return (print_error(ALLOC_FAIL, NULL), free_charray(split), \
		free(line), 0);
	rgb_split = ft_split(join, ',');
	free(join);
	if (!check_rgb(info, rgb_split, line, split))
		return (free(*split), free(split), free(line), 0);
	free_charray(rgb_split);
	return (free(*split), free(split), free(line), 1);
}
