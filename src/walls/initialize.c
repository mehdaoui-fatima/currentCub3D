/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 11:02:43 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/02 11:13:06 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

t_cub3d	*initialize(t_cub3d *cubdata)
{
	cubdata->cx = 0;
	cubdata->x = 0;
	cubdata->hit = 0;
	cubdata->mapx = (int)(cubdata->posx);
	cubdata->mapy = (int)(cubdata->posy);
	cubdata->movespeed = 0.15;
	cubdata->rotspeed = 0.045;
	cubdata->img.h = -1;
	cubdata->img.w = -1;
	return (cubdata);
}

void	texture(t_cub3d *cubdata)
{
	cubdata->texture[0].image_ptr = mlx_xpm_file_to_image(cubdata->connection,
	cubdata->tex.west, &cubdata->texture[0].w, &cubdata->texture[0].h);
	cubdata->texture[0].data = (int*)mlx_get_data_addr(
	cubdata->texture[0].image_ptr, &(cubdata->texture[0].bpp),
	&(cubdata->texture[0].size), &(cubdata->texture[0].endian));
	cubdata->texture[1].image_ptr = mlx_xpm_file_to_image(cubdata->connection,
	cubdata->tex.east, &cubdata->texture[1].w, &cubdata->texture[1].h);
	cubdata->texture[1].data = (int*)mlx_get_data_addr(
	cubdata->texture[1].image_ptr, &(cubdata->texture[1].bpp),
	&(cubdata->texture[1].size), &(cubdata->texture[1].endian));
	cubdata->texture[2].image_ptr = mlx_xpm_file_to_image(cubdata->connection,
	cubdata->tex.north, &cubdata->texture[2].w, &cubdata->texture[2].h);
	cubdata->texture[2].data = (int*)mlx_get_data_addr(
	cubdata->texture[2].image_ptr, &(cubdata->texture[2].bpp),
	&(cubdata->texture[2].size), &(cubdata->texture[2].endian));
	cubdata->texture[3].image_ptr = mlx_xpm_file_to_image(cubdata->connection,
	cubdata->tex.south, &cubdata->texture[3].w, &cubdata->texture[3].h);
	cubdata->texture[3].data = (int*)mlx_get_data_addr(
	cubdata->texture[3].image_ptr, &(cubdata->texture[3].bpp),
	&(cubdata->texture[3].size), &(cubdata->texture[3].endian));
	cubdata->texture[4].image_ptr = mlx_xpm_file_to_image(cubdata->connection,
	cubdata->tex.sprite, &cubdata->texture[4].w, &cubdata->texture[4].h);
	cubdata->texture[4].data = (int*)mlx_get_data_addr(
	cubdata->texture[4].image_ptr, &(cubdata->texture[4].bpp),
	&(cubdata->texture[4].size), &(cubdata->texture[4].endian));
}
