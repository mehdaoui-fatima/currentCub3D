/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 09:59:23 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/03 09:31:24 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	draw_wall_perp(t_cub3d *cub)
{
	if (cub->side == 0 || cub->side == 2)
		cub->perpwalldist = (double)(cub->mapx - cub->posx +
		(1 - cub->stepx) / 2) / cub->raydirx;
	else
		cub->perpwalldist = (double)(cub->mapy - cub->posy +
		(1 - cub->stepy) / 2) / cub->raydiry;
}

void	draw_wall_h_w(t_cub3d *cub)
{
	cub->lineheight = (int)(cub->res.ry / cub->perpwalldist);
	cub->drawstart = -cub->lineheight / 2 + cub->res.ry / 2;
	if (cub->drawstart < 0)
		cub->drawstart = 0;
	cub->drawend = cub->lineheight / 2 + cub->res.ry / 2;
	if (cub->drawend >= cub->res.ry)
		cub->drawend = cub->res.ry - 1;
	if (cub->side == 0 || cub->side == 2)
		cub->wallx = cub->posy + cub->perpwalldist * cub->raydiry;
	else
		cub->wallx = cub->posx + cub->perpwalldist * cub->raydirx;
	cub->wallx -= floor((cub->wallx));
	cub->texx = (int)(cub->wallx * (double)TEXWIDTH);
	if (cub->side == 0 && cub->raydirx > 0)
		cub->texx = TEXWIDTH - cub->texx - 1;
	if (cub->side == 1 && cub->raydiry < 0)
		cub->texx = TEXWIDTH - cub->texx - 1;
	cub->step = 1.0 * TEXHEIGHT / cub->lineheight;
	cub->texpos = (cub->drawstart - cub->res.ry / 2 + cub->lineheight / 2)
	* cub->step;
}

void	each_side(int i, int x, t_cub3d *cub)
{
	if (cub->side == 0)
		cub->img.data[i * cub->res.rx + x] =
		cub->texture[2].data[cub->texx + cub->texy * cub->texture[2].h];
	else if (cub->side == 1)
		cub->img.data[i * cub->res.rx + x] =
		cub->texture[1].data[cub->texx + cub->texy * cub->texture[1].h];
	else if (cub->side == 2)
		cub->img.data[i * cub->res.rx + x] =
		cub->texture[3].data[cub->texx + cub->texy * cub->texture[3].h];
	else
		cub->img.data[i * cub->res.rx + x] =
		cub->texture[0].data[cub->texx + cub->texy * cub->texture[0].h];
}

void	drawline(int x, int start, int end, t_cub3d *cub)
{
	int i;

	i = -1;
	while (++i < cub->res.ry)
	{
		if (i < start)
			cub->img.data[i * cub->res.rx + x] = cub->rgb.ceilcolor;
		else if (i <= end)
		{
			cub->texy = (int)cub->texpos;
			cub->texpos += cub->step;
			each_side(i, x, cub);
		}
		else if (i > end)
			cub->img.data[i * cub->res.rx + x] = cub->rgb.floorcolor;
	}
}
