/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 16:35:52 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/03/11 12:52:24 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  CUB3D_H
# define  CUB3D_H

#include <mlx.h>
#include <math.h>
#include <fcntl.h>
#include <stdio.h> //..perror
#include <stdlib.h>
#include <errno.h> //errno
#include <string.h> //strerror
#include "../libft/libft.h"
#include "../gnl/get_next_line.h"
#include "../minilibx/mlx_png.h"


#define texWidth 64
#define texHeight 64
#define rot_right 124
#define rot_left 123
#define move_towards 13
#define move_backwards 1
#define move_right 2
#define move_left 0
#define exit_ 53
#define uDiv 1
#define vDiv 1
#define vMove 0.0


#define MAX_WIDTH 2560
#define MAX_HEIGHT 1440
#define NUM_ARG 0
#define DUP_LINE 1
#define WRONG_DATA 2
#define INVALID_LINE 3
#define INVALID_RGB 4
#define INVALID_PATH 5
#define NON_NEGATIVE 6
#define RESOLUTION 7
#define TEXTURE 8
#define MAP_FILE 9
#define CEILING 10
#define FLOOR 11
#define MISSING 12
#define IMPOSTER 13
#define NOSPACESNEEDED 14
#define INVALID_MAP 15
#define MAP 16
#define DIR 17
#define EXTENSION 18
#define FILE 19





typedef struct s_getline {
	char *line;
	int r;
	int fd;
	char **newline;
	char **new;
	int res;
	int spaces;
} t_getline;




typedef struct s_resolution {
	long long rx;
	long long ry;
} t_resolution  ;




typedef struct s_rgb {

	int cr;
	int cg;
	int cb;
	int fr;
	int fg;
	int fb;
	int ceilColor;
	int floorColor;
} t_rgb;


typedef struct s_texture{

	char *north;
	char *south;
	char *west;
	char *east;
	char *sprite;
} t_texture ;




typedef struct s_err {
	int err;  
} t_err;

typedef struct s_map {
	int index;
	char **map;
	char **tmp;
	char **new_map;
	int  **worldMap;
	int map_len;
	int max_len;
} t_map ;


typedef struct s_img
{
	void   *image_ptr;//to under
	int *data;  /* it shoud be char * but we use int so it
								 can represent 4char=1pixel
								each index will represent one complete 
								color of a pixel
								 */
	int bpp;//to 
	int endian;
	int size;
	int h;
	int w;
} t_img;


typedef struct s_sprite
{
	double x;
	double y;
	int spriteorder;
	double spritedistance;
} t_sprite;


typedef struct s_cub3d{

	t_getline getl;
	t_resolution res;
	t_rgb rgb;
	t_texture tex;
	t_err err;
	t_map maps;
	t_img img;
	t_img texture[5];//array of images for texture
	t_sprite *sprites;
	int *connection; 
	int *window;
	double posx; //player position 
	double posy;
	double dirx; //player direction 
	double diry;
	double planx; //plan coordinates
	double plany;
	double cx;    //camera cordinate x
	double x;     // counter //changed when try to do sprites double->int
	double raydirx;  // ray coordinate
	double raydiry;
	int mapx;
	int mapy;
	double sidedistx;
	double sidedisty;
	double perpwalldist;
	int stepx;
	int stepy;
	int hit;
	int side;
	double deltadistx;
	double deltadisty;
	int color ;
	double movespeed;
	double rotspeed;
	double olddirx;
	double oldplanx;

	int lineHeight;
	int drawStart ;
	int drawEnd;
	int change;
	int plus;//for lookup lookdown
	int jump;//too jump
	int jumpback;//how much we will jump
	char *path;
	double wallx;
	int texx;
	double  step;
	double  texpos;
	int  texy;
	int screenHeight;
	int screenWidth;
	int numsprites;
	double *zbuffer;
	double spritex;
	double spritey;
	int spriteheight;
	int drawstarty;
	int drawendy;
	int spritewidth;
	int drawstartx;
	int drawendx;
	int texX;
	int d ;
	int texY;
	int spritescreenx;
	int vmovescreen;
	int stripe;
	double transformx;
	double transformy;
	double invdet;
}				t_cub3d;


t_cub3d      *initialize(t_cub3d *cubdata);//init cub3d
t_cub3d      *parsing(t_cub3d *cubdata, char *argv); //parsing .cub
//void        resolution(t_cub3d *cubdata, char *(micub_err[]));
void        resolution(t_cub3d *cubdata, char *micub_err[]);
void        ft_errors(char *error, char *str);
int         ft_isnumber(char *s);
int         ft_len(char **newline);
void        ft_free(char **s);
int         ft_spaces(t_cub3d *cubdata);
void        ft_ceil_floor(t_cub3d *cubdata, char*micub_err[]);
void        ft_textures(t_cub3d *cubdata, char*micub_err[]);
int         ft_missingdata(t_cub3d *cubdata);
void        ft_map(t_cub3d *cubdata, char *micub_err[]);
void        ft_new_map(t_cub3d *cubdata);
void        ft_mapvalid(t_cub3d *cubdata, char *micub_err[]);
void        ft_create_worldMap(t_cub3d *cubdata);

void        draw_sprites(t_cub3d *cubdata);


void	draw_wall_cx(t_cub3d *cubdata);
void	draw_wall_delta( t_cub3d *cubdata);
void	draw_wall_side(t_cub3d *cubdata);
void	draw_wall_dda(t_cub3d *cubdata);
void	draw_wall_perp(t_cub3d *cubdata);
void	draw_wall_h_w(t_cub3d *cubdata);
void  drawline(int x, int start, int end, t_cub3d *cubdata);



void        draw_wall(t_cub3d *cubdata);// drawing walls
int         ft_key_press(int keycode, t_cub3d *cubdata);//to be able to used by main
void        texture(t_cub3d *cubdata);
void        draw_sprites(t_cub3d *cubdata);



//int draw_screen(t_data *cubdata);
void		make_bmp(t_cub3d *cub);


#endif
