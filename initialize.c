
#include "cub3d.h"


// t_cub3d    *initialize(t_cub3d  *cub3d)
// {
// 	cub3d->posx = 4 + 0.5;
// 	cub3d->posy = 6 + 0.5;
// 	cub3d->dirx = ;
// 	cub3d->diry = 1;
// 	cub3d->planx = 0.66;
// 	cub3d->plany = 0;
// 	cub3d->cx = 0;
// 	cub3d->x = 0;
// 	cub3d->hit = 0;
// 	cub3d->mapx = (int)cub3d->posx;
// 	cub3d->mapy= (int)cub3d->posy;
// 	cub3d->movespeed = 7;
// 	cub3d->rotspeed = 0.2;
// 	//double olddirx ;
// 	//double oldplanx;
// 	// cub3d->change = 0;
// 	// cub3d->plus = 0;
// 	// cub3d->jump = 0;
// 	// cub3d->jumpback = 0;
// 	cub3d->img.h = -1;
// 	cub3d->img.w = -1;
// 	return (cub3d);
// }

/*
			cubdata->cub3d.dirx = -1;
				cubdata->cub3d.diry = 0;
				cubdata->cub3d.planx = 0;
				cubdata->cub3d.plany = 0.66;
*/





t_cub3d    *initialize(t_cub3d  *cub3d)
{
	cub3d->posx = 4 + 0.5;
	cub3d->posy = 6 + 0.5;
	cub3d->dirx = 0;
	cub3d->diry = 1;
	cub3d->planx = 0.66;
	cub3d->plany = 0;
	cub3d->cx = 0;
	cub3d->x = 0;
	cub3d->hit = 0;
	cub3d->mapx = (int)cub3d->posx;
	cub3d->mapy= (int)cub3d->posy;
	cub3d->movespeed = 7;
	cub3d->rotspeed = 0.2;
	//double olddirx ;
	//double oldplanx;
	// cub3d->change = 0;
	// cub3d->plus = 0;
	// cub3d->jump = 0;
	// cub3d->jumpback = 0;
	cub3d->img.h = -1;
	cub3d->img.w = -1;
	return (cub3d);
}