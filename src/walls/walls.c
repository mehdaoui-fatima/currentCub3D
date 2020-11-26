
#include "../../header/cub3d.h"


void    draw_wall(t_cub3d *cub)
{
	cub->x = 0;
	while (cub->x < cub->res.rx) 
	{
		draw_wall_cx(cub);//done
		draw_wall_delta(cub);//done
		draw_wall_side(cub);//done
		cub->hit = 0;
		draw_wall_dda(cub);
		draw_wall_perp(cub);
		draw_wall_h_w(cub);
		drawline(cub->x, cub->drawStart, cub->drawEnd, cub);
		cub->x++;
		//printf("%f\n",cub->perpwalldist);
		//TODO needed for sprites
		cub->zbuffer[(int)(cub->x)] = cub->perpwalldist;	
		//printf("%f\n",zbuffer[(int)(cub->x)]);
	}
	draw_sprites(cub);
}



// int draw_screen(t_cub3d *cub){
// 	write(1, "hola\n", 5);
// 	mlx_clear_window(cub->connection, cub->window);
// 	mlx_destroy_image(cub->connection, cub->img.image_ptr);
// 	cub->img.image_ptr = mlx_new_image(cub->connection, cub->rx, cub->ry);
// 	cub->img.data = (int*)mlx_get_data_addr(cub->img.image_ptr, &(cub->img.bpp), &(cub->img.size), &(cub->img.endian));
// 	draw_wall(cub);
// 	mlx_put_image_to_window(cub->connection, cub->window, cub->img.image_ptr, 0, 0);
// 	return 0;
// }



