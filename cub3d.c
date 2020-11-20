/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 12:52:45 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/03/11 12:52:57 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



//https://github.com/Glagan/42-cub3d

#include "cub3d.h"

int main(int argc, char **argv)
{
	if(argc < 2)
		ft_putstr_fd("too few arguments\n", 1);
	else if(argc > 2)
		ft_putstr_fd("too many arguments\n", 1);
	else
	{
		t_data cubdata;

		parsing(&cubdata, argv[1]);
		initialize(&cubdata);
		//printf("\nposx :%f\nposy: %f\ndirx: %f\ndiry: %f\nplanx: %f\nplany: %f\n",
		// cubdata.cub3d.posx, cubdata.cub3d.posy, cubdata.cub3d.dirx, cubdata.cub3d.diry,
		// cubdata.cub3d.planx, cubdata.cub3d.plany);
		//printf("from file parcig: %f %f\n",cubdata.cub3d.posx,cubdata.cub3d.posy);
		cubdata.cub3d.connection = mlx_init();
		texture(&cubdata);
		cubdata.cub3d.window = mlx_new_window(cubdata.cub3d.connection, cubdata.rx, cubdata.ry, "Cub3D");
		cubdata.cub3d.img.image_ptr = mlx_new_image(cubdata.cub3d.connection, cubdata.rx, cubdata.ry);
		cubdata.cub3d.img.data = (int*)mlx_get_data_addr(cubdata.cub3d.img.image_ptr, &(cubdata.cub3d.img.bpp), &(cubdata.cub3d.img.size), &(cubdata.cub3d.img.endian));
		draw_wall(&cubdata);//to draw walls for the first time the screen is opened 
		mlx_put_image_to_window(cubdata.cub3d.connection, cubdata.cub3d.window, cubdata.cub3d.img.image_ptr, 0, 0);
		mlx_hook(cubdata.cub3d.window, 2, 0, ft_key_press, &cubdata);
		mlx_hook(cubdata.cub3d.window, 17, 0, ft_key_press, &cubdata);
		//mlx_loop_hook(cubdata.cub3d.connection, draw_screen, &cubdata);
		mlx_loop(cubdata.cub3d.connection);
	}
	return (0);
}























