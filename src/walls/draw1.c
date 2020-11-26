#include "../../header/cub3d.h"

void	draw_wall_cx(t_cub3d *cub)
{	
	cub->cx = (2 * cub->x / cub->res.rx) - 1; // all the values are limited between [-1,1]
	cub->raydirx = cub->dirx + cub->planx * cub->cx;
	cub->raydiry = cub->diry + cub->plany * cub->cx;
}

void	draw_wall_delta( t_cub3d *cub)
{
	cub->deltadistx = (cub->raydiry == 0)? 0 : ((cub->raydirx == 0)? 1 : fabs(1 / cub->raydirx));
	cub->deltadisty = (cub->raydirx == 0) ? 0 : ((cub->raydiry == 0) ? 1 : fabs(1 / cub->raydiry));
	cub->mapx = (int)(cub->posx);
	cub->mapy= (int)(cub->posy);
	//printf("\n|%f %f %d %d|\n",cub->posx,cub->posy, cub->mapx, cub->mapy);
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
		cub->sidedisty = (cub->mapy+ 1.0 - cub->posy) * cub->deltadisty;
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
		}//++
		if(cub->side == 0 && cub->raydirx > 0)
		{
			cub->side = 2;
		}
		 if(cub->side == 1 && cub->raydiry < 0)
		{
			cub->side = 3;
		}//++
		//printf("---%d    %d----\n", cub->mapx, cub->mapy);
		if (cub->maps.worldMap[cub->mapx][cub->mapy] == 1) 
			cub->hit = 1;
	} 
}