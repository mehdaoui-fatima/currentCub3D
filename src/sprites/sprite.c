#include "../../header/cub3d.h"

void	tri(t_cub3d *cub)
{
	int j;
	int k;
	t_sprite tmp;

	j = -1;
	k = -1;
	while(++j < cub->numsprites)
	{
		k = -1;
		while (++k < cub->numsprites - j - 1)
		{
			if (cub->sprites[k].spritedistance < cub->sprites[k+1].spritedistance) 
			{
				
				tmp = cub->sprites[k];
				cub->sprites[k] =  cub->sprites[k + 1];
				cub->sprites[k + 1] = tmp;
			}
		}
	}
}


void draw_sprites(t_cub3d *cub)
{

	int i;
	int y;
	
	i = -1;
	while(++i < cub->numsprites)
	{
		cub->sprites[i].spriteorder = i;
		cub->sprites[i].spritedistance = ((cub->posx - cub->sprites[i].x) * (cub->posx - cub->sprites[i].x)) 
		+ ((cub->posy - cub->sprites[i].y)*(cub->posy - cub->sprites[i].y));
		//printf("distance:%d %d\n",cub->sprites[i].x,cub->sprites[i].y);
	}
	tri(cub);
	i = -1;
	while (++i < cub->numsprites)
	{
		cub->spritex = cub->sprites[i].x - cub->posx;
		cub->spritey = cub->sprites[i].y - cub->posy;
		double invDet = 1.0 / (cub->planx * cub->diry - cub->dirx * cub->plany); 
		cub->transformx = invDet * (cub->diry * cub->spritex - cub->dirx * cub->spritey);
		cub->transformy = invDet * (-cub->plany * cub->spritex + cub->planx * cub->spritey); 
		cub->spritescreenx = (int)((cub->res.rx / 2) * (1 + cub->transformx / cub->transformy));
		cub->vmovescreen = (int)(vMove / cub->transformy);
		cub->spriteheight = abs((int)(cub->res.ry / (cub->transformy))) / vDiv; 
		cub->drawstarty = -cub->spriteheight / 2 + cub->res.ry / 2 + cub->vmovescreen;
		if(cub->drawstarty < 0) cub->drawstarty = 0;
		cub->drawendy = cub->spriteheight / 2 + cub->res.ry / 2 + cub->vmovescreen;
		if(cub->drawendy >= cub->res.ry) cub->drawendy = cub->res.ry - 1;

		cub->spritewidth = abs((int)(cub->res.ry / (cub->transformy))) / uDiv;
		cub->drawstartx = -cub->spritewidth / 2 + cub->spritescreenx;
		if(cub->drawstartx < 0) cub->drawstartx = 0;
		cub->drawendx = cub->spritewidth / 2 + cub->spritescreenx;
		if(cub->drawendx >= cub->res.rx) cub->drawendx = cub->res.rx - 1;

		cub->stripe = cub->drawstartx;

		while (cub->stripe < cub->drawendx)
		{
			cub->texX = (int)(256 * (cub->stripe - (-cub->spritewidth / 2 + cub->spritescreenx)) * texWidth / cub->spritewidth) / 256;
			if(cub->transformy > 0 && cub->stripe > 0 && cub->stripe < cub->res.rx && cub->transformy < cub->zbuffer[cub->stripe])
			{
				y = cub->drawstarty;
				while (y < cub->drawendy) 
				{
					cub->d = (y-cub->vmovescreen) * 256 - cub->res.ry * 128 + cub->spriteheight * 128; 
					cub->texY = ((cub->d * texHeight) / cub->spriteheight) / 256;
					if (cub->texture[4].data[cub->texX + cub->texY * cub->texture[4].h])
					cub->img.data[y * cub->res.rx + cub->stripe] = cub->texture[4].data[cub->texX + cub->texY * cub->texture[4].h];
					y++;
				}
			}
			cub->stripe++;
		}
	}
}

