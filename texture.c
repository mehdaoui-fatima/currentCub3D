
#include <stdio.h>
#include<stdlib.h>
#include "./minilibx/mlx.h"
#include "./minilibx/mlx_png.h"


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
} t_img;


void    drawline(int x, int start, int end, int h, int w, t_img img)
{
	int i = 0;

	while (i <  h)
	{
		if(i <= start)
			img.data[i * w + x] = 0x81DBF2;
		else
		{
			if (i <= end)
				img.data[i * w + x] = 0xEFA719;
			else
				img.data[i * w + x] = 0x81DBF2;	
		}
		i++;
	}
}


int main()
{
    t_img img;
    char *file_name = "pics/colorstone.png";
    int w = 1000;
    int h = 1000;
    
    void  *mlx_ptr = mlx_init();
    void *mlx_win = mlx_new_window(mlx_ptr,w,h,"cub3d");
    img.image_ptr = mlx_new_image(mlx_ptr,w,h);
    int  *read_img = mlx_png_file_to_image(mlx_ptr,file_name,&w,&h);
    img.data = (int*)mlx_get_data_addr(img.image_ptr,&img.bpp,&img.size,&img.endian);
    drawline();
    mlx_put_image_to_window(mlx_ptr, mlx_win,img.image_ptr,0,0);


    mlx_loop(mlx_ptr);
    return(0);
}




void	texture(t_cub3d *cub3d)
{
	int w = 64;
	int h = 64;

	cub3d->texture[0].image_ptr = mlx_png_file_to_image(cub3d->connection, "./pics/colorstone.png", &cub3d->texture[0].w, &cub3d->texture[0].h);
	cub3d->texture[0].data = (int*)mlx_get_data_addr(cub3d->connection, &(cub3d->texture[0].bpp), &(cub3d->texture[0].size),&(cub3d->texture[0].endian));
}