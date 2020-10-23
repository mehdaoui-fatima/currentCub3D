
#include <stdio.h>
#include<stdlib.h>
#include "./minilibx/mlx.h"
//#include "mlx_png.h"




int main()
{
    int w = 1000;
    int h = 1000;
    void  *mlx_ptr = mlx_init();
    void *mlx_win = mlx_new_window(mlx_ptr,w,h,"cub3d");
    mlx_loop(mlx_ptr);
   
    //mlx_hook(cub3d.window,  ft_key_press, &cub3d);
     char *file_name = "pics/colorstone.png";
     int  *read_img = mlx_png_file_to_image(mlx_ptr,file_name,&w,&h);


    return(0);
}