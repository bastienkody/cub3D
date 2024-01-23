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
# include <math.h>
# include <X11/keysym.h>

/*	parsing error	*/
# define BAD_ARG_NB "Bad number of argument"
# define BAD_CONFIG_NAME "Bad config file name (*.cub expected)"
# define BADLINE "Following line format is not acceptable:"
# define NOTCONF "Texture/rgb config is not completed yet but the \
following line does not comply with config format:"
# define LACK_FO "Not all infos collected while EOF found in"
# define BAD_NBR "Overflow or non digit detected in rgb values within the \
following line:"
# define EMPTY "Empty line within or after the map info is not acceptable"
# define BAD_MAP_CHAR "Bad map char found whithin line:"
# define BAD_PPOS "Not exactly one player position wihthin the map"
# define BAD_WALL "Map is not completely surrounded by walls"
# define BAD_SPACE "A space was found next to a walkable path on the following \
line:"
# define TOO_SMALL "Map is too small (row or column < 3 char)"
# define MULTI_DEF "Multiple definition of the following identifier:"
# define BAD_XPM "Only accepting xpm file for texture, not:"
# define BAD_XPM_FILE "mlx_xpm_file_to_img returned null with path:"
# define NO_FETCH_RES "Could not fetch screen resolution from system (the game \
window is designed to be 1920x1080)"
# define LOWER_RES "Screen resolution is lower than expected (1920x1080), you \
might change hardware to fully enjoy the game :)"

/*	generic errors */
# define ALLOC_FAIL "Malloc error - cub3D exiting"
# define BAD_INI "Mlx initialization failed. Perhaps check envp before retry"
# define BAD_WIN "Mlx window creation failed"
# define IMAGE_FAIL "Creation of an image failed - cub3D exiting"

/*	teleport errors */
# define T_W "You can't teleport to wall or void (in x"
# define T_WB "). Please aim walkable floor"
# define T_OUT "Out of range teleportation (in "
# define T_OUTB "). Aim walkable floor"

/*	alpha const	*/
# define MAPCHAR "NSEW01 "
# define NSEW "NSEW"
# define TRUC ""

/*	num const	*/
# define ALLOR 3
# define TILE_S 64
# define WIN_W 1920
# define WIN_H 1010
# define MENUBAR_H 70
# define PLAYER_ICON_TO_MMAP_TILE_RATIO 10

/*	player velocity	*/
# define VELO_M 0.2
# define VELO_R M_PI/48

/*	raycast	*/
# define PITCH 0
# define CROUCH_VAL 300
# define PLANE_ANG_TO_DIR 0.72

/*	minimap : 12x12 rects of tile 16x16	*/
# define MNAP_TS 16
# define MNAP_W 192
# define MNAP_H 192

/*	counter	*/
# ifndef INTRO_COUNTER
#	define INTRO_COUNTER 750
# endif

/*	outro menu position	*/
# define X 730
# define X_S 1181
# define Y 511
# define Y_S 563
# define Y_OFST 79

/*	colors	*/
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
#define GREY 0x00808080
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF

/*	typedef	*/
typedef bool			t_bool;
typedef unsigned int	uint;

typedef struct s_raycast
{
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		side;
	double	raydirx;
	double	raydiry;
	double	sidex;
	double	sidey;
	double	deltax;
	double	deltay;
	double	pwall;
	int		lineh;
	int		start;
	int		end;
	int		whatext;
	double	wallx;
	int		xtext;

}				t_raycast;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}				t_img;

typedef struct s_parser
{
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
	double			planex;
	double			planey;
}				t_parser;

typedef struct s_info
{
	void			*ptr;
	void			*win;
	char			**map;
	int				mh;
	int				mw;
	unsigned int	floor;
	unsigned int	ceil;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	int				crouch;
	t_bool			is_intro;
	t_bool			is_outro;
	t_bool			is_maximap;
	int				mmap_tile_s;
	int				mmap_bordx;
	int				mmap_bordy;
	t_img			*intro1;
	t_img			*intro2;
	t_img			*outro[3];
	t_img			*bg_default;
	t_img			*n_text;
	t_img			*s_text;
	t_img			*w_text;
	t_img			*e_text;
	t_img			*minimap;
	t_img			*maximap;
	t_img			*rc;
	t_img			*rc_buf;
}				t_info;

/*	display	*/
void	run(t_info *info);
int		init_display(t_info *info, t_parser *pars);
int		display_manager(t_info *info);
void	draw_minimap(t_info *info);

/*	raycast - dda	*/
void	dda(t_raycast *rc, char **map);
void	dda_prep(t_raycast *rc, double posx, double posy);
int		raycast_launcher(t_info *info);

/*	outro - pause */
void	outro(t_info *info);

/*	maximap	*/
void	draw_player_icon(t_info *info, t_img *img_map, int tile_s);
void	draw_first_maximap(t_info *info);
void	maximap_display(t_info *info);
void	maximap_teleport(int but, unsigned int x, unsigned int y, t_info *info);

/*	actions / movements	*/
void	crouch_uncrouch(t_info *info);
void 	key_movement(int keycode, t_info *info);

/*	hooks	*/
int		outro_mouse_inputs(int but, int x, int y, t_info *info);
int		mouse_inputs(int button, int x, int y, t_info *info);
int		key_inputs(int keycode, t_info *info);

/*	drawers	*/
void	pixel_w(t_img *img, int x, int y, int color);
uint	get_color(t_img *img, int x, int y);
void	img_to_img(t_img *src, t_img *dst, int og[2], int dim[2]);
void	line_w(t_img *img, int a[2], int b[2], int color);
void	draw_vert_line(t_img *img, int x, int y[2], int color);
void	draw_rect(t_img *img, int og[2], int dim[2], int color);
void	draw_border(t_img *img, int og[2], int dim[2], int color);
void	draw_rect_w_border(t_img *img, int og[2], int dim[2], int color);

/*	img	*/
t_img	*create_image(void *mlx_ptr, int w, int h);
t_img	*create_xpm_image(void *mlx_ptr, char *path, int w, int h);

/*	parsing	*/
t_parser	*main_parser(int argc, char **argv);
int		get_texture(char *line, char **split, t_parser *pars);
int		get_rgb(char *line, char **split, t_parser *pars);
int		map_checker(t_parser *pars);

/*	parsing utils	*/
int		tab_len(char **tab);
int		longest_line(char **map);
int		is_str_only(char *str, char *valid);
int		is_texture_line(char **split);
int		is_rgb_line(char **split);
void	update_map_on(int *map_on, t_parser *pars);
int		count_c_in_str(char *str, char c);
int		argb_hex(unsigned char a, unsigned char r, unsigned char g, \
				unsigned char b);

/*	printers	*/
void	print_error(char *str1, char *str2);
void	print_raycast(t_raycast *rc);
void	print_info(t_info *info);
void	print_rc(t_raycast *rc);

/*	free	*/
int		end_free(t_info *info);
void	end_parser(t_parser *pars);

#endif
