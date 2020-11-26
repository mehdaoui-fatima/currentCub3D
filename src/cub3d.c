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

#include "../header/cub3d.h"

int main(int argc, char **argv)
{
	if(argc < 2)
		ft_putstr_fd("too few arguments\n", 1);
	else if(argc > 2)
		ft_putstr_fd("too many arguments\n", 1);
	else
	{
		t_cub3d cub;
		parsing(&cub, argv[1]);
		initialize(&cub);
		cub.connection = mlx_init();
		texture(&cub);
		cub.window = mlx_new_window(cub.connection, cub.res.rx, cub.res.ry, "Cub3D");
		cub.img.image_ptr = mlx_new_image(cub.connection, cub.res.rx,cub.res.ry);
		cub.img.data = (int*)mlx_get_data_addr(cub.img.image_ptr, &(cub.img.bpp), &(cub.img.size), &(cub.img.endian));
		draw_wall(&cub);//to draw walls for the first time the screen is opened 
		mlx_put_image_to_window(cub.connection, cub.window, cub.img.image_ptr, 0, 0);
		mlx_hook(cub.window, 2, 0, ft_key_press, &cub);
		mlx_hook(cub.window, 17, 0, ft_key_press, &cub);
		//mlx_loop_hook(cubdata.cub3d.connection, draw_screen, &cubdata);
		//ft_free((char**)cubdata.worldMap);
		mlx_loop(cub.connection);
		
	}
	return (0);
}























