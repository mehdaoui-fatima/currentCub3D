/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 20:55:50 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/03 10:12:41 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	tri(t_cub3d *cub)
{
	int			j;
	int			k;
	t_sprite	tmp;

	j = -1;
	while (++j < cub->numsprites)
	{
		k = -1;
		while (++k < cub->numsprites - j - 1)
		{
			if (cub->sprites[k].spritedistance <
			cub->sprites[k + 1].spritedistance)
			{
				tmp = cub->sprites[k];
				cub->sprites[k] = cub->sprites[k + 1];
				cub->sprites[k + 1] = tmp;
			}
		}
	}
}

void	sprite_cal(int i, t_cub3d *c)
{
	double invdet;

	c->spritex = c->sprites[i].x - c->posx;
	c->spritey = c->sprites[i].y - c->posy;
	invdet = 1.0 / (c->planx * c->diry - c->dirx * c->plany);
	c->transformx = invdet * (c->diry * c->spritex - c->dirx * c->spritey);
	c->transformy = invdet * (-c->plany * c->spritex + c->planx * c->spritey);
	c->spritescreenx = (int)((c->res.rx / 2) *
	(1 + c->transformx / c->transformy));
	c->vmovescreen = (int)(VMOVE / c->transformy);
	c->spriteheight = abs((int)(c->res.ry / (c->transformy))) / VDIV;
	c->drawstarty = -c->spriteheight / 2 + c->res.ry / 2 + c->vmovescreen;
	if (c->drawstarty < 0)
		c->drawstarty = 0;
	c->drawendy = c->spriteheight / 2 + c->res.ry / 2 + c->vmovescreen;
	if (c->drawendy >= c->res.ry)
		c->drawendy = c->res.ry - 1;
	c->spritewidth = abs((int)(c->res.ry / (c->transformy))) / UDIV;
	c->drawstartx = -c->spritewidth / 2 + c->spritescreenx;
	if (c->drawstartx < 0)
		c->drawstartx = 0;
	c->drawendx = c->spritewidth / 2 + c->spritescreenx;
	if (c->drawendx >= c->res.rx)
		c->drawendx = c->res.rx - 1;
	c->stripe = c->drawstartx;
}

void	sprite_dr(t_cub3d *cub)
{
	int y;

	cub->texx = (int)(256 * (cub->stripe -
	(-cub->spritewidth / 2 + cub->spritescreenx))
	* TEXWIDTH / cub->spritewidth) / 256;
	if (cub->transformy > 0 && cub->stripe > 0
	&& cub->stripe < cub->res.rx
	&& cub->transformy < cub->zbuffer[cub->stripe])
	{
		y = cub->drawstarty;
		while (y < cub->drawendy)
		{
			cub->d = (y - cub->vmovescreen) * 256 -
			cub->res.ry * 128 + cub->spriteheight * 128;
			cub->texy = ((cub->d * TEXHEIGHT) / cub->spriteheight) / 256;
			if (cub->texture[4].data[cub->texx +
			cub->texy * cub->texture[4].h])
				cub->img.data[y * cub->res.rx + cub->stripe] =
			cub->texture[4].data[cub->texx + cub->texy * cub->texture[4].h];
			y++;
		}
	}
}

void	draw_sprites(t_cub3d *cub)
{
	int i;

	i = -1;
	while (++i < cub->numsprites)
	{
		cub->sprites[i].spriteorder = i;
		cub->sprites[i].spritedistance = ((cub->posx - cub->sprites[i].x)
		* (cub->posx - cub->sprites[i].x))
		+ ((cub->posy - cub->sprites[i].y) * (cub->posy - cub->sprites[i].y));
	}
	tri(cub);
	i = -1;
	while (++i < cub->numsprites)
	{
		sprite_cal(i, cub);
		while (cub->stripe < cub->drawendx)
		{
			sprite_dr(cub);
			cub->stripe++;
		}
	}
}
