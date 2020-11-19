
#include "cub3d.h"

int worldMap[9][10]=
{
  {1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},//
  {1,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1}
};



void	texture(t_cub3d *cub3d)
{

	// W 
	cub3d->texture[0].image_ptr = mlx_png_file_to_image(cub3d->connection, "./pics/colorstone.png", &cub3d->texture[0].w, &cub3d->texture[0].h);
	cub3d->texture[0].data = (int*)mlx_get_data_addr(cub3d->texture[0].image_ptr, &(cub3d->texture[0].bpp), &(cub3d->texture[0].size),&(cub3d->texture[0].endian));
	
	//E
	cub3d->texture[1].image_ptr = mlx_png_file_to_image(cub3d->connection, "./pics/wood.png", &cub3d->texture[1].w, &cub3d->texture[1].h);
	cub3d->texture[1].data = (int*)mlx_get_data_addr(cub3d->texture[1].image_ptr, &(cub3d->texture[1].bpp), &(cub3d->texture[1].size),&(cub3d->texture[1].endian));

	//north 
	cub3d->texture[2].image_ptr = mlx_png_file_to_image(cub3d->connection, "./pics/mossy.png", &cub3d->texture[2].w, &cub3d->texture[2].h);
	cub3d->texture[2].data = (int*)mlx_get_data_addr(cub3d->texture[2].image_ptr, &(cub3d->texture[2].bpp), &(cub3d->texture[2].size),&(cub3d->texture[2].endian));
	
	// South
	cub3d->texture[3].image_ptr = mlx_png_file_to_image(cub3d->connection, "./pics/bluestone.png", &cub3d->texture[3].w, &cub3d->texture[3].h);
	cub3d->texture[3].data = (int*)mlx_get_data_addr(cub3d->texture[3].image_ptr, &(cub3d->texture[3].bpp), &(cub3d->texture[3].size),&(cub3d->texture[3].endian));
}

void	draw_wall_cx(t_cub3d *cub3d)
{		
	cub3d->cx = (2 * cub3d->x / screenWidth) - 1; // all the values are limited between [-1,1]
	cub3d->raydirx = cub3d->dirx + cub3d->planx * cub3d->cx;
	cub3d->raydiry = cub3d->diry + cub3d->plany * cub3d->cx;
}

void	draw_wall_delta( t_cub3d *cub3d)
{
	cub3d->deltadistx = (cub3d->raydiry == 0)? 0 : ((cub3d->raydirx == 0)? 1 : fabs(1/cub3d->raydirx));
	cub3d->deltadisty = (cub3d->raydirx == 0) ? 0 : ((cub3d->raydiry == 0) ? 1 : fabs(1 / cub3d->raydiry));
	cub3d->mapx = (int)cub3d->posx;
	cub3d->mapy= (int)cub3d->posy;
}

void	draw_wall_side(t_cub3d *cub3d)
{
	if (cub3d->raydirx < 0)
	{
		cub3d->stepx = -1;
		cub3d->sidedistx = (cub3d->posx - cub3d->mapx) * cub3d->deltadistx;
	}
	else
	{
		cub3d->stepx = 1;
		cub3d->sidedistx = (cub3d->mapx + 1.0 - cub3d->posx) * cub3d->deltadistx;
	}
	if (cub3d->raydiry < 0)
	{
		cub3d->stepy = -1;
		cub3d->sidedisty = (cub3d->posy - cub3d->mapy) * cub3d->deltadisty;
	}
	else
	{
		cub3d->stepy = 1;
		cub3d->sidedisty = (cub3d->mapy+ 1.0 - cub3d->posy) * cub3d->deltadisty;
	}
}

 void	draw_wall_dda(t_cub3d *cub3d)
 {
	while (cub3d->hit == 0)
	{
		if (cub3d->sidedistx < cub3d->sidedisty)
		{
			cub3d->sidedistx += cub3d->deltadistx;
			cub3d->mapx += cub3d->stepx;
			cub3d->side = 0;
		}
		else
		{
			cub3d->sidedisty += cub3d->deltadisty;
			cub3d->mapy += cub3d->stepy;
			cub3d->side = 1;
		}//++
		if(cub3d->side == 0 && cub3d->raydirx > 0)
		{
			cub3d->side = 2;
		}
		 if(cub3d->side == 1 && cub3d->raydiry < 0)
		{
			cub3d->side = 3;
		}//++
		if (worldMap[cub3d->mapx][cub3d->mapy] == 1) 
			cub3d->hit = 1;
	} 
 }



void	draw_wall_perp(t_cub3d *cub3d)
{
	if (cub3d->side == 0 || cub3d->side == 2)//++
		cub3d->perpwalldist = (double)(cub3d->mapx - cub3d->posx + (1 - cub3d->stepx) / 2) / cub3d->raydirx;
	else          
		cub3d->perpwalldist = (double)(cub3d->mapy- cub3d->posy + (1 - cub3d->stepy) / 2) / cub3d->raydiry;
}


void	draw_wall_h_w(t_cub3d *cub3d)
{
	cub3d->lineHeight = (int)(screenHeight / cub3d->perpwalldist);
	cub3d->drawStart = -cub3d->lineHeight / 2 + screenHeight / 2;
	if(cub3d->drawStart < 0)
		cub3d->drawStart = 0;
	cub3d->drawEnd = cub3d->lineHeight / 2 + screenHeight / 2;
	if(cub3d->drawEnd >= screenHeight)
		cub3d->drawEnd = screenHeight - 1;
		//++
	if(cub3d->side == 0 || cub3d->side == 2)// thats why it woorks and not get pixeled
		cub3d->wallx = cub3d->posy + cub3d->perpwalldist * cub3d->raydiry;
	else
		cub3d->wallx = cub3d->posx + cub3d->perpwalldist * cub3d->raydirx;
	cub3d->wallx -= floor((cub3d->wallx));//0.5
	cub3d->texx = (int)(cub3d->wallx * (double)texWidth);
	if(cub3d->side == 0 && cub3d->raydirx > 0) 
		cub3d->texx = texWidth - cub3d->texx - 1;
    if(cub3d->side == 1 && cub3d->raydiry < 0) 
		cub3d->texx = texWidth - cub3d->texx - 1;
	cub3d->step = 1.0 * texHeight / cub3d->lineHeight;
    cub3d->texpos = (cub3d->drawStart - screenHeight / 2 + cub3d->lineHeight / 2) * cub3d->step;
}

//cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->txt[0].img_data[cub->texX + cub->texY * cub->txt[0].w];
//cub->img.h >= cub->drawStart && cub->img.h <= cub->drawEnd
void    drawline(int x, int start, int end, t_cub3d *cub3d)
{
	//ft_putstr_fd("\nhere\n",1);
	int i = 0;
	while (i  <  screenHeight)
	{
		if (i <= start)
			cub3d->img.data[i * screenWidth + x ] = 0x6a736a;
		else 
		{
			if (i <= end)
			{
				
				cub3d->texy = (int)cub3d->texpos;
				cub3d->texpos += cub3d->step;
				
				
				if(cub3d->side == 0)
					cub3d->img.data[i * screenWidth + x ] = cub3d->texture[2].data[cub3d->texx + cub3d->texy * cub3d->texture[2].h];
				else if(cub3d->side == 1)
					cub3d->img.data[i * screenWidth + x ] = cub3d->texture[1].data[cub3d->texx + cub3d->texy * cub3d->texture[1].h];
				else if (cub3d->side == 2)
					cub3d->img.data[i * screenWidth + x ] = cub3d->texture[3].data[cub3d->texx + cub3d->texy * cub3d->texture[3].h];
				else
					cub3d->img.data[i * screenWidth + x ] = cub3d->texture[0].data[cub3d->texx + cub3d->texy * cub3d->texture[0].h];	
			}
			else
				cub3d->img.data[i * screenWidth + x ] = 0xcdf5cb ;
		}
	
		// if(cub3d->img.h  <= start)
		// 	cub3d->img.data[cub3d->img.h  * screenWidth + x] = cub3d->texture[0].data[cub3d->texx + cub3d->texture[0].w * cub3d->texy];
		// else
		// {
		// 	if (cub3d->img.h  <= end)
		// 		cub3d->img.data[cub3d->img.h  * screenWidth + x] = cub3d->color;
		// 	else
		// 		cub3d->img.data[cub3d->img.h  * screenWidth + x] = 0xEFA719;	
		// }
		i++;
	}
}

void    draw_wall(t_cub3d *cub3d)
{
	cub3d->x = 0;
	while (cub3d->x < screenWidth) 
	{
		draw_wall_cx(cub3d);//done
		draw_wall_delta(cub3d);//done
		draw_wall_side(cub3d);//done
		cub3d->hit = 0;
		draw_wall_dda(cub3d);
		draw_wall_perp(cub3d);
		draw_wall_h_w(cub3d);
		drawline(cub3d->x, cub3d->drawStart, cub3d->drawEnd, cub3d);
		cub3d->x++;
	}
	//printf("****%d\n",cub3d->drawStart);
}


int ft_key_press(int keycode, t_cub3d *cub3d)
{
//	printf("%d",keycode);
	if (cub3d->movespeed > 1)
		cub3d->movespeed *= 0.1;
	if (keycode == move_towards)
	{
		if(worldMap[(int)(cub3d->posx + cub3d->dirx * cub3d->movespeed)][(int)(cub3d->posy)] == 0) 
			cub3d->posx += cub3d->dirx * cub3d->movespeed;
		if(worldMap[(int)(cub3d->posx)][(int)(cub3d->posy + cub3d->diry * cub3d->movespeed)] == 0)
		cub3d->posy += cub3d->diry * cub3d->movespeed;
	}
	if (keycode == move_backwards)
	{
		if(worldMap[(int)(cub3d->posx - cub3d->dirx * cub3d->movespeed)][(int)(cub3d->posy)] == 0)
			cub3d->posx -= cub3d->dirx * cub3d->movespeed;
		if(worldMap[(int)(cub3d->posx)][(int)(cub3d->posy - cub3d->diry * cub3d->movespeed)] == 0)
			cub3d->posy -= cub3d->diry * cub3d->movespeed;
	}
	if (keycode == move_right)
	{
		cub3d->olddirx = cub3d->dirx;
		cub3d->dirx = cub3d->dirx * cos(-cub3d->rotspeed) - cub3d->diry * sin(-cub3d->rotspeed);
		cub3d->diry = cub3d->olddirx * sin(-cub3d->rotspeed) + cub3d->diry * cos(-cub3d->rotspeed);
		cub3d->oldplanx = cub3d->planx;
		cub3d->planx = cub3d->planx * cos(-cub3d->rotspeed) - cub3d->plany * sin(-cub3d->rotspeed);
		cub3d->plany = cub3d->oldplanx * sin(-cub3d->rotspeed) + cub3d->plany * cos(cub3d->rotspeed);
	}
	if (keycode == move_left)
	{
		cub3d->olddirx =  cub3d->dirx;
		cub3d->dirx =  cub3d->dirx * cos( cub3d->rotspeed) -  cub3d->diry * sin( cub3d->rotspeed);
		cub3d->diry =  cub3d->olddirx * sin(cub3d->rotspeed) +  cub3d->diry * cos( cub3d->rotspeed);
		cub3d->oldplanx =  cub3d->planx;
		cub3d->planx =  cub3d->planx * cos(cub3d->rotspeed) -  cub3d->plany * sin( cub3d->rotspeed);
		cub3d->plany =  cub3d->oldplanx * sin(cub3d->rotspeed) + cub3d->plany * cos(cub3d->rotspeed);
	}
	if (keycode == exit_)
		exit(1);
	mlx_clear_window(cub3d->connection, cub3d->window);
	mlx_destroy_image(cub3d->connection, cub3d->img.image_ptr);
	cub3d->img.image_ptr = mlx_new_image(cub3d->connection, screenWidth, screenHeight);
	cub3d->img.data = (int*)mlx_get_data_addr(cub3d->img.image_ptr, &(cub3d->img.bpp), &(cub3d->img.size), &(cub3d->img.endian));
	draw_wall(cub3d);
	mlx_put_image_to_window(cub3d->connection, cub3d->window, cub3d->img.image_ptr, 0, 0);
	return (0);
}


