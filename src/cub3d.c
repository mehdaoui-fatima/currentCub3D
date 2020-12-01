/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 12:52:45 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/01 12:04:40 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

int exitcross(t_cub3d *cub)
{
	mlx_clear_window(cub->connection, cub->window);
	exit(1);
}



int main(int argc, char **argv)
{
	if (argc != 2 && argc != 3)
		ft_errors("Number of args are not correct","");
	else
	{
		if (argc == 3 && (ft_strcmp(argv[2],"--save") != 0))
			ft_errors("args are not correct", "");
		t_cub3d cub;
		parsing(&cub, argv[1]);
		initialize(&cub);
		cub.connection = mlx_init();
		texture(&cub);
		cub.window = mlx_new_window(cub.connection, cub.res.rx, cub.res.ry, "Cub3d");
		cub.img.image_ptr = mlx_new_image(cub.connection, cub.res.rx,cub.res.ry);
		cub.img.data = (int*)mlx_get_data_addr(cub.img.image_ptr, &(cub.img.bpp), &(cub.img.size), &(cub.img.endian));
		draw_wall(&cub);//to draw walls for the first time the screen is opened
		if (argc == 3 && (ft_strcmp(argv[2],"--save") == 0))
			make_bmp(&cub);
		mlx_put_image_to_window(cub.connection, cub.window, cub.img.image_ptr, 0, 0);
		mlx_hook(cub.window, 2, 0, ft_key_pressed, &cub);
		mlx_hook(cub.window, 3, 0, ft_key_released, &cub);
		mlx_hook(cub.window, 17, 0, exitcross, &cub);
		mlx_loop_hook(cub.connection, ft_keys, &cub);
		mlx_loop(cub.connection);
	}
	
	return (0);
}























