/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:07:33 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/02 14:38:24 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

int	ft_key_pressed(int keycode, t_cub3d *cub)
{
	cub->keyboard[keycode] = 1;
	return (0);
}

int	ft_key_released(int keycode, t_cub3d *cub)
{
	cub->keyboard[keycode] = 0;
	return (0);
}

int	exitcross(t_cub3d *cub)
{
	mlx_clear_window(cub->connection, cub->window);
	exit(1);
}

int	ft_keys(t_cub3d *cub)
{
	move_righ_left(cub);
	movetowards_backwards(cub);
	rotate(cub);
	if (cub->keyboard[EXIT_])
		exit(1);
	mlx_clear_window(cub->connection, cub->window);
	mlx_destroy_image(cub->connection,
	cub->img.image_ptr);
	cub->img.image_ptr = mlx_new_image(cub->connection,
	cub->res.rx, cub->res.ry);
	cub->img.data = (int*)mlx_get_data_addr(cub->img.image_ptr,
	&(cub->img.bpp), &(cub->img.size), &(cub->img.endian));
	draw_wall(cub);
	mlx_put_image_to_window(cub->connection, cub->window,
	cub->img.image_ptr, 0, 0);
	return (0);
}
