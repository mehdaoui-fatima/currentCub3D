/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 12:14:57 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/02 14:38:24 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	move_righ_left(t_cub3d *cub)
{
	if (cub->keyboard[MOVE_RIGHT])
	{
		if (cub->maps.worldmap[(int)
		(cub->posx + cub->planx * cub->movespeed)][(int)(cub->posy)] == 0)
			cub->posx += cub->planx * cub->movespeed;
		if (cub->maps.worldmap[(int)
		(cub->posx)][(int)(cub->posy + cub->plany * cub->movespeed)] == 0)
			cub->posy += cub->plany * cub->movespeed;
	}
	if (cub->keyboard[MOVELEFT])
	{
		if (cub->maps.worldmap[(int)
		(cub->posx - cub->planx * cub->movespeed)][(int)(cub->posy)] == 0)
			cub->posx -= cub->planx * cub->movespeed;
		if (cub->maps.worldmap[(int)
		(cub->posx)][(int)(cub->posy - cub->plany * cub->movespeed)] == 0)
			cub->posy -= cub->plany * cub->movespeed;
	}
}

void	movetowards_backwards(t_cub3d *cub)
{
	if (cub->keyboard[MOVETOWARDS])
	{
		if (cub->maps.worldmap[(int)
		(cub->posx + cub->dirx * cub->movespeed)][(int)(cub->posy)] == 0)
			cub->posx += cub->dirx * cub->movespeed;
		if (cub->maps.worldmap[(int)
		(cub->posx)][(int)(cub->posy + cub->diry * cub->movespeed)] == 0)
			cub->posy += cub->diry * cub->movespeed;
	}
	if (cub->keyboard[MOVEBACKWARDS])
	{
		if (cub->maps.worldmap[(int)
		(cub->posx - cub->dirx * cub->movespeed)][(int)(cub->posy)] == 0)
			cub->posx -= cub->dirx * cub->movespeed;
		if (cub->maps.worldmap[(int)
		(cub->posx)][(int)(cub->posy - cub->diry * cub->movespeed)] == 0)
			cub->posy -= cub->diry * cub->movespeed;
	}
}

void	rotate(t_cub3d *c)
{
	if (c->keyboard[ROTRIGHT])
	{
		c->olddirx = c->dirx;
		c->dirx = c->dirx * cos(-c->rotspeed) - c->diry * sin(-c->rotspeed);
		c->diry = c->olddirx * sin(-c->rotspeed) + c->diry * cos(-c->rotspeed);
		c->oldplanx = c->planx;
		c->planx = c->planx * cos(-c->rotspeed) - c->plany * sin(-c->rotspeed);
		c->plany = c->oldplanx * sin(-c->rotspeed)
		+ c->plany * cos(c->rotspeed);
	}
	if (c->keyboard[ROTLEFT])
	{
		c->olddirx = c->dirx;
		c->dirx = c->dirx * cos(c->rotspeed) - c->diry * sin(c->rotspeed);
		c->diry = c->olddirx * sin(c->rotspeed) + c->diry * cos(c->rotspeed);
		c->oldplanx = c->planx;
		c->planx = c->planx * cos(c->rotspeed) - c->plany * sin(c->rotspeed);
		c->plany = c->oldplanx * sin(c->rotspeed) + c->plany * cos(c->rotspeed);
	}
}
