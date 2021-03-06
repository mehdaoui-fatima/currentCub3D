/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:35:52 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/03 09:58:39 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include "../libft/libft.h"
# include "../gnl/get_next_line.h"
# define TEXWIDTH 64
# define TEXHEIGHT 64
# define ROTRIGHT 124
# define ROTLEFT 123
# define MOVETOWARDS 13
# define MOVEBACKWARDS 1
# define MOVE_RIGHT 2
# define MOVELEFT 0
# define EXIT_ 53
# define UDIV 1
# define VDIV 1
# define VMOVE 0.0
# define MAX_WIDTH 2560
# define MAX_HEIGHT 1440
# define NUM_ARG 0
# define DUP_LINE 1
# define WRONG_DATA 2
# define INVALID_LINE 3
# define INVALID_RGB 4
# define INVALID_PATH 5
# define NON_NEGATIVE 6
# define RESOLUTION 7
# define TEXTURE 8
# define MAP_FILE 9
# define CEILING 10
# define FLOOR 11
# define MISSING 12
# define IMPOSTER 13
# define NOSPACESNEEDED 14
# define INVALID_MAP 15
# define MAP 16
# define DIR 17
# define EXTENSION 18
# define FILE 19

static char		*(g_micub_err[]) =
{
	"Unexpected number of arguments, ",
	"Duplicate line, ",
	"Must contain only integers, ",
	"Incorrect Line, ",
	"RGB format not correct, values must be in the 0..255 range, ",
	"Open image failed. path is not correct, ",
	"Width and Height must be non-negative, ",
	"Resolution",
	"Texture path",
	"Map file",
	"Ceiling",
	"Floor",
	"Missing values,",
	"Imposter line, ",
	"No spaces needed at the start of the line, ",
	"Invalid map, ",
	"Map",
	"Only one of N,S,E or W is needed for the player’s start position, ",
	"Invalid extension .png required, ",
	"Invalid extension fileName.cub required, "
};

typedef	struct	s_getline
{
	char	*line;
	int		r;
	int		fd;
	char	**newline;
	char	**new;
	int		res;
	int		spaces;
}				t_getline;

typedef struct	s_resolution
{
	long long rx;
	long long ry;
}				t_resolution;

typedef struct	s_rgb
{
	int cr;
	int cg;
	int cb;
	int fr;
	int fg;
	int fb;
	int ceilcolor;
	int floorcolor;
}				t_rgb;

typedef struct	s_texture
{
	char *north;
	char *south;
	char *west;
	char *east;
	char *sprite;
}				t_texture;

typedef struct	s_err
{
	int err;
}				t_err;

typedef struct	s_map
{
	int		index;
	char	**map;
	char	**tmp;
	char	**new_map;
	int		**worldmap;
	int		map_len;
	int		max_len;
}				t_map;

typedef struct	s_img
{
	void	*image_ptr;
	int		*data;
	int		bpp;
	int		endian;
	int		size;
	int		h;
	int		w;
}				t_img;

typedef struct	s_sprite
{
	double	x;
	double	y;
	int		spriteorder;
	double	spritedistance;
}				t_sprite;

typedef struct	s_var
{
	int		i;
	int		j;
	int		len;
	char	*str;
	int		len_j;
	int		len_i;
	char	a;
	char	b;
	char	c;
	char	d;
	int		len_next;
	int		len_previous;
}				t_var;

typedef struct	s_cub3d
{
	t_getline		getl;
	t_resolution	res;
	t_rgb			rgb;
	t_texture		tex;
	t_err			err;
	t_map			maps;
	t_img			img;
	t_img			texture[5];
	t_sprite		*sprites;
	int				keyboard[300];
	int				*connection;
	int				*window;
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planx;
	double			plany;
	double			cx;
	double			x;
	double			raydirx;
	double			raydiry;
	int				mapx;
	int				mapy;
	double			sidedistx;
	double			sidedisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	double			deltadistx;
	double			deltadisty;
	int				color;
	double			movespeed;
	double			rotspeed;
	double			olddirx;
	double			oldplanx;
	int				lineheight;
	int				drawstart;
	int				drawend;
	int				change;
	int				jumpback;
	char			*path;
	double			wallx;
	int				texx;
	double			step;
	double			texpos;
	int				texy;
	int				numsprites;
	double			*zbuffer;
	double			spritex;
	double			spritey;
	int				spriteheight;
	int				drawstarty;
	int				drawendy;
	int				spritewidth;
	int				drawstartx;
	int				drawendx;
	int				d;
	int				spritescreenx;
	int				vmovescreen;
	int				stripe;
	double			transformx;
	double			transformy;
	double			invdet;
}				t_cub3d;

t_cub3d			*initialize(t_cub3d *cubdata);
t_cub3d			*parsing(t_cub3d *cubdata, char *argv);
void			resolution(t_cub3d *cubdata);
void			ft_errors(char *error, char *str);
int				ft_isnumber(char *s);
int				ft_len(char **newline);
void			ft_free(char **s);
int				ft_spaces(t_cub3d *cubdata);
void			ft_ceil_floor(t_cub3d *cubdata);
void			ft_textures(t_cub3d *cubdata);
int				ft_missingdata(t_cub3d *cubdata);
void			ft_map(t_cub3d *cubdata);
void			ft_new_map(t_cub3d *cubdata);
void			ft_mapvalid(t_cub3d *cubdata);
void			ft_create_worldmap(t_cub3d *cubdata);
void			draw_sprites(t_cub3d *cubdata);
void			draw_wall_cx(t_cub3d *cubdata);
void			draw_wall_delta(t_cub3d *cubdata);
void			draw_wall_side(t_cub3d *cubdata);
void			draw_wall_dda(t_cub3d *cubdata);
void			draw_wall_perp(t_cub3d *cubdata);
void			draw_wall_h_w(t_cub3d *cubdata);
void			drawline(int x, int start, int end, t_cub3d *cubdata);
void			draw_wall(t_cub3d *cubdata);
int				ft_keys(t_cub3d *cubdata);
int				ft_key_pressed(int keycode, t_cub3d *cub);
int				ft_key_released(int keycode, t_cub3d *cub);
int				exitcross(t_cub3d *cub);
void			texture(t_cub3d *cubdata);
void			draw_sprites(t_cub3d *cubdata);
void			first_last_line(char *first, char *last);
void			ft_borders(char c1, char c2);
int				ft_surrounded(char a, char b, char c, char d);
double			*create_dir_plan(double a, double b, double c, double d);
void			ft_dir_plan(t_cub3d *cub, double *tab);
void			move_righ_left(t_cub3d *cub);
void			movetowards_backwards(t_cub3d *cub);
void			rotate(t_cub3d *cub);
void			make_bmp(t_cub3d *cub);
#endif
