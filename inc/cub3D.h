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
# include "../libs/mlx/mlx.h"
# include "../libs/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>
# include <X11/keysym.h>

/*	error parsing msg	*/
# define BAD_ARG_NB "Bad number of argument"
# define BAD_CONFIG_NAME "Bad config file name (*.cub expected)"
# define BADLINE "Following line format is not acceptable:"
# define NOTCONF "Texture/rgb config is not completed yet but the \
following line does not comply with config format:"
# define LACK_INFO "Not all infos collected while EOF found in"
# define BAD_NBR "Overflow or non digit detected in rgb values within the \
following line:"
# define EMPTY "Empty line within the map info is not acceptable"
# define BAD_MAP_CHAR "Bad map char found whithin line:"
# define BAD_PPOS "Not exactly one player position wihthin the map"
# define BAD_WALL "Map is not completely surrounded by walls"
# define TOO_SMALL "Map is too small (row or column < 3 char)"
# define MULTI_DEF "Multiple definition of the following identifier:"
# define BAD_XPM "Only accepting xpm file for texture, not:"
# define BAD_XPM_FILE "mlx_xpm_file_to_img returned null with path:"

/*	generic errors */
# define ALLOC_FAIL "Malloc error - cub3D exiting"
# define BAD_INI "Mlx initialization failed. Perhaps check envp before retry"
# define BAD_WIN "Mlx window creation failed"

/*	alpha const	*/
# define MAPCHAR "NSEW01 "
# define NSEW "NSEW"

/*	num const	*/
# define WIN_WIDTH 1080
# define WIN_HEIGHT 720
# define INTRO_COUNTER_MAC_INTEL 30
# define INTRO_COUNTER_UBU 750

/*	colors	*/
# define WHITE 0x00FFFFFF

/*	typedef	*/
typedef bool	t_bool;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_info
{
	void			*ptr;
	void			*win;
	char			**map;
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	unsigned int	floor_rgb;
	t_bool			ceil;
	unsigned int	ceil_rgb;
	t_bool			floor;
	int				pposx;
	int				pposy;
	int				pdirx;
	int				pdiry;
	t_bool			is_intro;
	t_img			*intro1;
	t_img			*intro2;
}				t_info;

/*	display	*/
int		init_display(t_info *info);
void	pixel_w(t_img *img, int x, int y, int color);
void	line_w(t_img *img, int a[2], int b[2], int color);

/*	hooks	*/
int		close_window(t_info *info);
int		key_inputs(int keycode, t_info *info);
int		disp_intro(t_info *info);

/*	img	*/
t_img	*create_image(void *mlx_ptr, int w, int h);
t_img	*create_xpm_image(void *mlx_ptr, char *path, int w, int h);

/*	parsing	*/
t_info	*main_parser(int argc, char **argv);
int		get_texture(char *line, char **split, t_info *info);
int		get_rgb(char *line, char **split, t_info *info);
int		map_checker(t_info *info);

/*	parsing utils	*/
int		tab_len(char **tab);
int		is_str_only(char *str, char *valid);
int		is_texture_line(char **split);
int		is_rgb_line(char **split);
void	update_map_on(int *map_on, t_info *info);
int		count_c_in_str(char *str, char c);
int		argb_hex(unsigned char a, unsigned char r, unsigned char g, \
				unsigned char b);

/*	printers	*/
void	print_error(char *str1, char *str2);
void	print_info(t_info *info);

/*	free	*/
void	end_free(t_info *info);

#endif
