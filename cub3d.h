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
#include "./libft/libft.h"
#include "./gnl/get_next_line.h"
#include "./minilibx/mlx_png.h"




#define texWidth 64
#define texHeight 64
#define max_width 1024
#define max_height 768
#define rot_right 124
#define rot_left 123
#define move_towards 13
#define move_backwards 1
#define move_right 2
#define move_left 0
#define exit_ 53


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
    t_img img;
    t_img texture[5];//array of images for texture
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
    
}				t_cub3d;


// used to parse map.cub
typedef struct s_data{
  char *line;
  int r;
  int fd;
  long long rx;
  long long ry;
  char **newline;
  char **new;
  int cr;
  int cg;
  int cb;
  int fr;
  int fg;
  int fb;
	int res;
  char *north;
  char *south;
  char *west;
  char *east;
  char *sprite;
  int err;
  int index;
  int spaces;
  char **map;
  int map_len;
  int max_len;// max len 
  char **new_map;
  int  **worldMap;
  int ceilColor;
  int floorColor;
  t_cub3d cub3d;
  t_sprite *sprites;



}				t_data;


t_data      *initialize(t_data *cubdata);//init cub3d
t_data      *parsing(t_data *cubdata, char *argv); //parsing .cub
void        draw_wall(t_data *cubdata);// drawing walls
int         ft_key_press(int keycode, t_data *cubdata);//to be able to used by main
void        texture(t_data *cubdata);
void        draw_sprites(t_data *cubdata);
void        ft_free(char **s);


//int draw_screen(t_data *cubdata);



#endif
