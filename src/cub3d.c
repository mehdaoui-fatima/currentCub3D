/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 12:52:45 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/02 14:04:58 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/cub3d.h"

void	args_err(int argc, char **argv)
{
	if (argc != 2 && argc != 3)
		ft_errors("Number of args are not correct", "");
	if (argc == 3 && (ft_strcmp(argv[2], "--save") != 0))
		ft_errors("args are not correct", "");
}

int		main(int argc, char **argv)
{
	t_cub3d c;

	args_err(argc, argv);
	parsing(&c, argv[1]);
	initialize(&c);
	c.connection = mlx_init();
	texture(&c);
	c.window = mlx_new_window(c.connection, c.res.rx, c.res.ry, "Cub3d");
	c.img.image_ptr = mlx_new_image(c.connection, c.res.rx, c.res.ry);
	c.img.data = (int*)mlx_get_data_addr(c.img.image_ptr,
	&(c.img.bpp), &(c.img.size), &(c.img.endian));
	draw_wall(&c);
	if (argc == 3 && (ft_strcmp(argv[2], "--save") == 0))
		make_bmp(&c);
	mlx_put_image_to_window(c.connection, c.window, c.img.image_ptr, 0, 0);
	mlx_hook(c.window, 2, 0, ft_key_pressed, &c);
	mlx_hook(c.window, 3, 0, ft_key_released, &c);
	mlx_hook(c.window, 17, 0, exitcross, &c);
	mlx_loop_hook(c.connection, ft_keys, &c);
	mlx_loop(c.connection);
	return (0);
}
