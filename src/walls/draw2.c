#include "../../header/cub3d.h"

void	draw_wall_perp(t_cub3d *cub)
{
	if (cub->side == 0 || cub->side == 2)//++
		cub->perpwalldist = (double)(cub->mapx - cub->posx + (1 - cub->stepx) / 2) / cub->raydirx;
	else          
		cub->perpwalldist = (double)(cub->mapy- cub->posy + (1 - cub->stepy) / 2) / cub->raydiry;
}

void	draw_wall_h_w(t_cub3d *cub)
{
	cub->lineHeight = (int)(cub->res.ry / cub->perpwalldist);
	cub->drawStart = -cub->lineHeight / 2 + cub->res.ry / 2;
	if(cub->drawStart < 0)
		cub->drawStart = 0;
	cub->drawEnd = cub->lineHeight / 2 + cub->res.ry / 2;
	if(cub->drawEnd >= cub->res.ry)
		cub->drawEnd = cub->res.ry - 1;
		//++
	if(cub->side == 0 || cub->side == 2)// thats why it woorks and not get pixeled
		cub->wallx = cub->posy + cub->perpwalldist * cub->raydiry;
	else
		cub->wallx = cub->posx + cub->perpwalldist * cub->raydirx;
	cub->wallx -= floor((cub->wallx));//0.5
	cub->texx = (int)(cub->wallx * (double)texWidth);
	if(cub->side == 0 && cub->raydirx > 0) 
		cub->texx = texWidth - cub->texx - 1;
    if(cub->side == 1 && cub->raydiry < 0) 
		cub->texx = texWidth - cub->texx - 1;
	cub->step = 1.0 * texHeight / cub->lineHeight;
    cub->texpos = (cub->drawStart - cub->res.ry / 2 + cub->lineHeight / 2) * cub->step;
	// printf("%f\n",cub->perpwalldist);

}

//cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->txt[0].img_data[cub->texX + cub->texY * cub->txt[0].w];
//cub->img.h >= cub->drawStart && cub->img.h <= cub->drawEnd
void    drawline(int x, int start, int end, t_cub3d *cub)
{
	//ft_putstr_fd("\nhere\n",1);
	int i = 0;
	while (i  < cub->res.ry)
	{
		if (i < start)
			cub->img.data[i * cub->res.rx + x ] = cub->rgb.ceilColor;
		else if (i <= end)
		{
			
			cub->texy = (int)cub->texpos;
			cub->texpos += cub->step;
			
			
			if(cub->side == 0)
				cub->img.data[i * cub->res.rx + x ] = cub->texture[2].data[cub->texx + cub->texy * cub->texture[2].h];
			else if(cub->side == 1)
				cub->img.data[i * cub->res.rx + x ] = cub->texture[1].data[cub->texx + cub->texy * cub->texture[1].h];
			else if (cub->side == 2)
				cub->img.data[i * cub->res.rx + x ] = cub->texture[3].data[cub->texx + cub->texy * cub->texture[3].h];
			else
				cub->img.data[i * cub->res.rx + x ] = cub->texture[0].data[cub->texx + cub->texy * cub->texture[0].h];	
		}
		else if (i > end)
			cub->img.data[i * cub->res.rx + x ] = cub->rgb.floorColor ;
	
		// if(cub->img.h  <= start)
		// 	cub->img.data[cub->img.h  * cub->rx + x] = cub->texture[0].data[cub->texx + cub->texture[0].w * cub->texy];
		// else
		// {
		// 	if (cub->img.h  <= end)
		// 		cub->img.data[cub->img.h  * cub->rx + x] = cub->color;
		// 	else
		// 		cub->img.data[cub->img.h  * cub->rx + x] = 0xEFA719;	
		// }
		i++;
	}
}
