/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 09:14:59 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/02 14:31:00 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	draw_wall_cx(t_cub3d *cub)
{
	cub->cx = (2 * cub->x / cub->res.rx) - 1;
	cub->raydirx = cub->dirx + cub->planx * cub->cx;
	cub->raydiry = cub->diry + cub->plany * cub->cx;
}

void	draw_wall_delta(t_cub3d *cub)
{
	if (cub->raydiry == 0)
		cub->deltadistx = 0;
	else
		cub->deltadistx = (cub->raydirx == 0) ? 1 : fabs(1 / cub->raydirx);
	if (cub->raydirx == 0)
		cub->deltadisty = 0;
	else
		cub->deltadisty = (cub->raydiry == 0) ? 1 : fabs(1 / cub->raydiry);
	cub->mapx = (int)(cub->posx);
	cub->mapy = (int)(cub->posy);
}

void	draw_wall_side(t_cub3d *cub)
{
	if (cub->raydirx < 0)
	{
		cub->stepx = -1;
		cub->sidedistx = (cub->posx - cub->mapx) * cub->deltadistx;
	}
	else
	{
		cub->stepx = 1;
		cub->sidedistx = (cub->mapx + 1.0 - cub->posx) * cub->deltadistx;
	}
	if (cub->raydiry < 0)
	{
		cub->stepy = -1;
		cub->sidedisty = (cub->posy - cub->mapy) * cub->deltadisty;
	}
	else
	{
		cub->stepy = 1;
		cub->sidedisty = (cub->mapy + 1.0 - cub->posy) * cub->deltadisty;
	}
}

void	draw_wall_dda(t_cub3d *cub)
{
	while (cub->hit == 0)
	{
		if (cub->sidedistx < cub->sidedisty)
		{
			cub->sidedistx += cub->deltadistx;
			cub->mapx += cub->stepx;
			cub->side = 0;
		}
		else
		{
			cub->sidedisty += cub->deltadisty;
			cub->mapy += cub->stepy;
			cub->side = 1;
		}
		if (cub->side == 0 && cub->raydirx > 0)
		{
			cub->side = 2;
		}
		if (cub->side == 1 && cub->raydiry < 0)
		{
			cub->side = 3;
		}
		if (cub->maps.worldmap[cub->mapx][cub->mapy] == 1)
			cub->hit = 1;
	}
}
