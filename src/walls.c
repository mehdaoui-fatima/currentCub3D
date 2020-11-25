
#include "cub3d.h"




void	tri(t_data *cubdata)
{
	int j;
	int k;
	t_sprite tmp;

	j = -1;
	k = -1;
	while(++j < cubdata->cub3d.numsprites)
	{
		k = -1;
		while (++k < cubdata->cub3d.numsprites - j - 1)
		{
			if (cubdata->sprites[k].spritedistance < cubdata->sprites[k+1].spritedistance) 
			{
				
				//printf("%f %f\n",cubdata->sprites[k].spritedistance,cubdata->sprites[k+1].spritedistance);
				tmp = cubdata->sprites[k];
				cubdata->sprites[k] =  cubdata->sprites[k + 1];
				cubdata->sprites[k + 1] = tmp;
			}
		}
	}

}



void draw_sprites(t_data *cubdata)
{

	int i;
	

	i = -1;
	
	while(++i < cubdata->cub3d.numsprites)
	{
		cubdata->sprites[i].spriteorder = i;
		cubdata->sprites[i].spritedistance = ((cubdata->cub3d.posx - cubdata->sprites[i].x) * (cubdata->cub3d.posx - cubdata->sprites[i].x)) 
		+ ((cubdata->cub3d.posy - cubdata->sprites[i].y)*(cubdata->cub3d.posy - cubdata->sprites[i].y));
		//printf("distance:%d %d\n",cubdata->sprites[i].x,cubdata->sprites[i].y);
	}
	tri(cubdata);
	for(int i = 0; i < cubdata->cub3d.numsprites; i++)
    {
      //translate sprite position to relative to camera
      double spriteX = cubdata->sprites[i].x - cubdata->cub3d.posx;
      double spriteY = cubdata->sprites[i].y - cubdata->cub3d.posy;
      double invDet = 1.0 / (cubdata->cub3d.planx * cubdata->cub3d.diry - cubdata->cub3d.dirx * cubdata->cub3d.plany); //required for correct matrix multiplication

      double transformX = invDet * (cubdata->cub3d.diry * spriteX - cubdata->cub3d.dirx * spriteY);
      double transformY = invDet * (-cubdata->cub3d.plany * spriteX + cubdata->cub3d.planx * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

      int spriteScreenX = (int)((cubdata->rx / 2) * (1 + transformX / transformY));

      //parameters for scaling and moving the sprites
      #define uDiv 1
      #define vDiv 1
      #define vMove 0.0
      int vMoveScreen = (int)(vMove / transformY);

      //calculate height of the sprite on screen
      int spriteHeight = abs((int)(cubdata->ry / (transformY))) / vDiv; //using "transformY" instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + cubdata->ry / 2 + vMoveScreen;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + cubdata->ry / 2 + vMoveScreen;
      if(drawEndY >= cubdata->ry) drawEndY = cubdata->ry - 1;

      //calculate width of the sprite
      int spriteWidth = abs((int)(cubdata->ry / (transformY))) / uDiv;
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= cubdata->ry) drawEndX = cubdata->ry - 1;

      //loop through every vertical stripe of the sprite on screen
      for(int stripe = drawStartX; stripe < drawEndX; stripe++)
      {
        int texX = (int)(256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256;
        //the conditions in the if are:
        //1) it's in front of camera plane so you don't see things behind you
        //2) it's on the screen (left)
        //3) it's on the screen (right)
        //4) ZBuffer, with perpendicular distance
        if(transformY > 0 && stripe > 0 && stripe < cubdata->rx && transformY < cubdata->cub3d.zbuffer[stripe])
		{
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y-vMoveScreen) * 256 - cubdata->ry * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * texHeight) / spriteHeight) / 256;
				if (cubdata->cub3d.texture[4].data[texX + texY * cubdata->cub3d.texture[4].h])
					cubdata->cub3d.img.data[y * cubdata->rx + stripe] = cubdata->cub3d.texture[4].data[texX + texY * cubdata->cub3d.texture[4].h];
			}
		}
	}
    }


	

 
}







void	texture(t_data *cubdata)
{

	// W 
	cubdata->cub3d.texture[0].image_ptr = mlx_png_file_to_image(cubdata->cub3d.connection, cubdata->west, &cubdata->cub3d.texture[0].w, &cubdata->cub3d.texture[0].h);
	cubdata->cub3d.texture[0].data = (int*)mlx_get_data_addr(cubdata->cub3d.texture[0].image_ptr, &(cubdata->cub3d.texture[0].bpp), &(cubdata->cub3d.texture[0].size),&(cubdata->cub3d.texture[0].endian));
	
	//E
	cubdata->cub3d.texture[1].image_ptr = mlx_png_file_to_image(cubdata->cub3d.connection, cubdata->east, &cubdata->cub3d.texture[1].w, &cubdata->cub3d.texture[1].h);
	cubdata->cub3d.texture[1].data = (int*)mlx_get_data_addr(cubdata->cub3d.texture[1].image_ptr, &(cubdata->cub3d.texture[1].bpp), &(cubdata->cub3d.texture[1].size),&(cubdata->cub3d.texture[1].endian));

	//north 
	cubdata->cub3d.texture[2].image_ptr = mlx_png_file_to_image(cubdata->cub3d.connection, cubdata->north, &cubdata->cub3d.texture[2].w, &cubdata->cub3d.texture[2].h);
	cubdata->cub3d.texture[2].data = (int*)mlx_get_data_addr(cubdata->cub3d.texture[2].image_ptr, &(cubdata->cub3d.texture[2].bpp), &(cubdata->cub3d.texture[2].size),&(cubdata->cub3d.texture[2].endian));
	
	// South
	cubdata->cub3d.texture[3].image_ptr = mlx_png_file_to_image(cubdata->cub3d.connection,cubdata->south, &cubdata->cub3d.texture[3].w, &cubdata->cub3d.texture[3].h);
	cubdata->cub3d.texture[3].data = (int*)mlx_get_data_addr(cubdata->cub3d.texture[3].image_ptr, &(cubdata->cub3d.texture[3].bpp), &(cubdata->cub3d.texture[3].size),&(cubdata->cub3d.texture[3].endian));

	cubdata->cub3d.texture[4].image_ptr = mlx_png_file_to_image(cubdata->cub3d.connection,cubdata->sprite, &cubdata->cub3d.texture[4].w, &cubdata->cub3d.texture[4].h);
	cubdata->cub3d.texture[4].data = (int*)mlx_get_data_addr(cubdata->cub3d.texture[4].image_ptr, &(cubdata->cub3d.texture[4].bpp), &(cubdata->cub3d.texture[4].size),&(cubdata->cub3d.texture[4].endian));
}

void	draw_wall_cx(t_data *cubdata)
{		
	cubdata->cub3d.cx = (2 * cubdata->cub3d.x / cubdata->rx) - 1; // all the values are limited between [-1,1]
	cubdata->cub3d.raydirx = cubdata->cub3d.dirx + cubdata->cub3d.planx * cubdata->cub3d.cx;
	cubdata->cub3d.raydiry = cubdata->cub3d.diry + cubdata->cub3d.plany * cubdata->cub3d.cx;
}

void	draw_wall_delta( t_data *cubdata)
{
	cubdata->cub3d.deltadistx = (cubdata->cub3d.raydiry == 0)? 0 : ((cubdata->cub3d.raydirx == 0)? 1 : fabs(1 / cubdata->cub3d.raydirx));
	cubdata->cub3d.deltadisty = (cubdata->cub3d.raydirx == 0) ? 0 : ((cubdata->cub3d.raydiry == 0) ? 1 : fabs(1 / cubdata->cub3d.raydiry));
	cubdata->cub3d.mapx = (int)(cubdata->cub3d.posx);
	cubdata->cub3d.mapy= (int)(cubdata->cub3d.posy);
	//printf("\n|%f %f %d %d|\n",cubdata->cub3d.posx,cubdata->cub3d.posy, cubdata->cub3d.mapx, cubdata->cub3d.mapy);
}

void	draw_wall_side(t_data *cubdata)
{
	if (cubdata->cub3d.raydirx < 0)
	{
		cubdata->cub3d.stepx = -1;
		cubdata->cub3d.sidedistx = (cubdata->cub3d.posx - cubdata->cub3d.mapx) * cubdata->cub3d.deltadistx;
	}
	else
	{
		cubdata->cub3d.stepx = 1;
		cubdata->cub3d.sidedistx = (cubdata->cub3d.mapx + 1.0 - cubdata->cub3d.posx) * cubdata->cub3d.deltadistx;
	}
	if (cubdata->cub3d.raydiry < 0)
	{
		cubdata->cub3d.stepy = -1;
		cubdata->cub3d.sidedisty = (cubdata->cub3d.posy - cubdata->cub3d.mapy) * cubdata->cub3d.deltadisty;
	}
	else
	{
		cubdata->cub3d.stepy = 1;
		cubdata->cub3d.sidedisty = (cubdata->cub3d.mapy+ 1.0 - cubdata->cub3d.posy) * cubdata->cub3d.deltadisty;
	}
}

 void	draw_wall_dda(t_data *cubdata)
 {
	while (cubdata->cub3d.hit == 0)
	{
		if (cubdata->cub3d.sidedistx < cubdata->cub3d.sidedisty)
		{
			cubdata->cub3d.sidedistx += cubdata->cub3d.deltadistx;
			cubdata->cub3d.mapx += cubdata->cub3d.stepx;
			cubdata->cub3d.side = 0;
		}
		else
		{
			cubdata->cub3d.sidedisty += cubdata->cub3d.deltadisty;
			cubdata->cub3d.mapy += cubdata->cub3d.stepy;
			cubdata->cub3d.side = 1;
		}//++
		if(cubdata->cub3d.side == 0 && cubdata->cub3d.raydirx > 0)
		{
			cubdata->cub3d.side = 2;
		}
		 if(cubdata->cub3d.side == 1 && cubdata->cub3d.raydiry < 0)
		{
			cubdata->cub3d.side = 3;
		}//++
		//printf("---%d    %d----\n", cubdata->cub3d.mapx, cubdata->cub3d.mapy);
		if (cubdata->worldMap[cubdata->cub3d.mapx][cubdata->cub3d.mapy] == 1) 
			cubdata->cub3d.hit = 1;
	} 
 }

void	draw_wall_perp(t_data *cubdata)
{
	if (cubdata->cub3d.side == 0 || cubdata->cub3d.side == 2)//++
		cubdata->cub3d.perpwalldist = (double)(cubdata->cub3d.mapx - cubdata->cub3d.posx + (1 - cubdata->cub3d.stepx) / 2) / cubdata->cub3d.raydirx;
	else          
		cubdata->cub3d.perpwalldist = (double)(cubdata->cub3d.mapy- cubdata->cub3d.posy + (1 - cubdata->cub3d.stepy) / 2) / cubdata->cub3d.raydiry;
}

void	draw_wall_h_w(t_data *cubdata)
{
	cubdata->cub3d.lineHeight = (int)(cubdata->ry / cubdata->cub3d.perpwalldist);
	cubdata->cub3d.drawStart = -cubdata->cub3d.lineHeight / 2 + cubdata->ry / 2;
	if(cubdata->cub3d.drawStart < 0)
		cubdata->cub3d.drawStart = 0;
	cubdata->cub3d.drawEnd = cubdata->cub3d.lineHeight / 2 + cubdata->ry / 2;
	if(cubdata->cub3d.drawEnd >= cubdata->ry)
		cubdata->cub3d.drawEnd = cubdata->ry - 1;
		//++
	if(cubdata->cub3d.side == 0 || cubdata->cub3d.side == 2)// thats why it woorks and not get pixeled
		cubdata->cub3d.wallx = cubdata->cub3d.posy + cubdata->cub3d.perpwalldist * cubdata->cub3d.raydiry;
	else
		cubdata->cub3d.wallx = cubdata->cub3d.posx + cubdata->cub3d.perpwalldist * cubdata->cub3d.raydirx;
	cubdata->cub3d.wallx -= floor((cubdata->cub3d.wallx));//0.5
	cubdata->cub3d.texx = (int)(cubdata->cub3d.wallx * (double)texWidth);
	if(cubdata->cub3d.side == 0 && cubdata->cub3d.raydirx > 0) 
		cubdata->cub3d.texx = texWidth - cubdata->cub3d.texx - 1;
    if(cubdata->cub3d.side == 1 && cubdata->cub3d.raydiry < 0) 
		cubdata->cub3d.texx = texWidth - cubdata->cub3d.texx - 1;
	cubdata->cub3d.step = 1.0 * texHeight / cubdata->cub3d.lineHeight;
    cubdata->cub3d.texpos = (cubdata->cub3d.drawStart - cubdata->ry / 2 + cubdata->cub3d.lineHeight / 2) * cubdata->cub3d.step;
	// printf("%f\n",cubdata->cub3d.perpwalldist);





}

//cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->txt[0].img_data[cub->texX + cub->texY * cub->txt[0].w];
//cub->img.h >= cub->drawStart && cub->img.h <= cub->drawEnd
void    drawline(int x, int start, int end, t_data *cubdata)
{
	//ft_putstr_fd("\nhere\n",1);
	int i = 0;
	while (i  <  cubdata->ry)
	{

		if (i <= start)
			cubdata->cub3d.img.data[i * cubdata->rx + x ] = cubdata->ceilColor;
		else 
		{
			if (i <= end)
			{
				
				cubdata->cub3d.texy = (int)cubdata->cub3d.texpos;
				cubdata->cub3d.texpos += cubdata->cub3d.step;
				
				
				if(cubdata->cub3d.side == 0)
					cubdata->cub3d.img.data[i * cubdata->rx + x ] = cubdata->cub3d.texture[2].data[cubdata->cub3d.texx + cubdata->cub3d.texy * cubdata->cub3d.texture[2].h];
				else if(cubdata->cub3d.side == 1)
					cubdata->cub3d.img.data[i * cubdata->rx + x ] = cubdata->cub3d.texture[1].data[cubdata->cub3d.texx + cubdata->cub3d.texy * cubdata->cub3d.texture[1].h];
				else if (cubdata->cub3d.side == 2)
					cubdata->cub3d.img.data[i * cubdata->rx + x ] = cubdata->cub3d.texture[3].data[cubdata->cub3d.texx + cubdata->cub3d.texy * cubdata->cub3d.texture[3].h];
				else
					cubdata->cub3d.img.data[i * cubdata->rx + x ] = cubdata->cub3d.texture[0].data[cubdata->cub3d.texx + cubdata->cub3d.texy * cubdata->cub3d.texture[0].h];	
			}
			else
				cubdata->cub3d.img.data[i * cubdata->rx + x ] = cubdata->floorColor ;
		}
	
		// if(cubdata->cub3d.img.h  <= start)
		// 	cubdata->cub3d.img.data[cubdata->cub3d.img.h  * cubdata->rx + x] = cubdata->cub3d.texture[0].data[cubdata->cub3d.texx + cubdata->cub3d.texture[0].w * cubdata->cub3d.texy];
		// else
		// {
		// 	if (cubdata->cub3d.img.h  <= end)
		// 		cubdata->cub3d.img.data[cubdata->cub3d.img.h  * cubdata->rx + x] = cubdata->cub3d.color;
		// 	else
		// 		cubdata->cub3d.img.data[cubdata->cub3d.img.h  * cubdata->rx + x] = 0xEFA719;	
		// }
		i++;
	}
}

void    draw_wall(t_data *cubdata)
{
	cubdata->cub3d.x = 0;
	cubdata->cub3d.zbuffer = (double*)malloc(sizeof(double) * cubdata->rx);
	
	//cubdata->cub3d.zbuffer[cubdata->rx]; //TODO check if it need to be not declared this way
	//printf("lenght%d\n",cubdata->rx);
	while (cubdata->cub3d.x < cubdata->rx) 
	{
		draw_wall_cx(cubdata);//done
		draw_wall_delta(cubdata);//done
		draw_wall_side(cubdata);//done
		cubdata->cub3d.hit = 0;
		draw_wall_dda(cubdata);
		draw_wall_perp(cubdata);
		draw_wall_h_w(cubdata);
		drawline(cubdata->cub3d.x, cubdata->cub3d.drawStart, cubdata->cub3d.drawEnd, cubdata);
		cubdata->cub3d.x++;
		//printf("%f\n",cubdata->cub3d.perpwalldist);
		//TODO needed for sprites
		cubdata->cub3d.zbuffer[(int)(cubdata->cub3d.x)] = cubdata->cub3d.perpwalldist;
		

		
		//printf("%f\n",zbuffer[(int)(cubdata->cub3d.x)]);
	}
	draw_sprites(cubdata);
}


int ft_key_press(int keycode, t_data *cubdata)
{
//	printf("%d",keycode);
	if (cubdata->cub3d.movespeed > 1)
		cubdata->cub3d.movespeed *= 0.1;
	if (keycode == move_right)
	{
		if(cubdata->worldMap[(int)(cubdata->cub3d.posx + cubdata->cub3d.planx * cubdata->cub3d.movespeed)][(int)(cubdata->cub3d.posy)] == 0) 
			cubdata->cub3d.posx += cubdata->cub3d.planx * cubdata->cub3d.movespeed;
		if(cubdata->worldMap[(int)(cubdata->cub3d.posx)][(int)(cubdata->cub3d.posy + cubdata->cub3d.plany* cubdata->cub3d.movespeed)] == 0)
		cubdata->cub3d.posy += cubdata->cub3d.plany* cubdata->cub3d.movespeed;
	}
	if (keycode == move_left)
	{
		if(cubdata->worldMap[(int)(cubdata->cub3d.posx - cubdata->cub3d.planx * cubdata->cub3d.movespeed)][(int)(cubdata->cub3d.posy)] == 0) 
			cubdata->cub3d.posx -= cubdata->cub3d.planx * cubdata->cub3d.movespeed;
		if(cubdata->worldMap[(int)(cubdata->cub3d.posx)][(int)(cubdata->cub3d.posy - cubdata->cub3d.plany* cubdata->cub3d.movespeed)] == 0)
			cubdata->cub3d.posy -= cubdata->cub3d.plany* cubdata->cub3d.movespeed;
	}
	if (keycode == move_towards)
	{
		if(cubdata->worldMap[(int)(cubdata->cub3d.posx + cubdata->cub3d.dirx * cubdata->cub3d.movespeed)][(int)(cubdata->cub3d.posy)] == 0) 
			cubdata->cub3d.posx += cubdata->cub3d.dirx * cubdata->cub3d.movespeed;
		if(cubdata->worldMap[(int)(cubdata->cub3d.posx)][(int)(cubdata->cub3d.posy + cubdata->cub3d.diry * cubdata->cub3d.movespeed)] == 0)
		cubdata->cub3d.posy += cubdata->cub3d.diry * cubdata->cub3d.movespeed;
	}
	if (keycode == move_backwards)
	{
		if(cubdata->worldMap[(int)(cubdata->cub3d.posx - cubdata->cub3d.dirx * cubdata->cub3d.movespeed)][(int)(cubdata->cub3d.posy)] == 0)
			cubdata->cub3d.posx -= cubdata->cub3d.dirx * cubdata->cub3d.movespeed;
		if(cubdata->worldMap[(int)(cubdata->cub3d.posx)][(int)(cubdata->cub3d.posy - cubdata->cub3d.diry * cubdata->cub3d.movespeed)] == 0)
			cubdata->cub3d.posy -= cubdata->cub3d.diry * cubdata->cub3d.movespeed;
	}
	if (keycode == rot_right)
	{
		cubdata->cub3d.olddirx = cubdata->cub3d.dirx;
		cubdata->cub3d.dirx = cubdata->cub3d.dirx * cos(-cubdata->cub3d.rotspeed) - cubdata->cub3d.diry * sin(-cubdata->cub3d.rotspeed);
		cubdata->cub3d.diry = cubdata->cub3d.olddirx * sin(-cubdata->cub3d.rotspeed) + cubdata->cub3d.diry * cos(-cubdata->cub3d.rotspeed);
		cubdata->cub3d.oldplanx = cubdata->cub3d.planx;
		cubdata->cub3d.planx = cubdata->cub3d.planx * cos(-cubdata->cub3d.rotspeed) - cubdata->cub3d.plany * sin(-cubdata->cub3d.rotspeed);
		cubdata->cub3d.plany = cubdata->cub3d.oldplanx * sin(-cubdata->cub3d.rotspeed) + cubdata->cub3d.plany * cos(cubdata->cub3d.rotspeed);
	}
	if (keycode == rot_left)
	{
		cubdata->cub3d.olddirx =  cubdata->cub3d.dirx;
		cubdata->cub3d.dirx =  cubdata->cub3d.dirx * cos( cubdata->cub3d.rotspeed) -  cubdata->cub3d.diry * sin( cubdata->cub3d.rotspeed);
		cubdata->cub3d.diry =  cubdata->cub3d.olddirx * sin(cubdata->cub3d.rotspeed) +  cubdata->cub3d.diry * cos( cubdata->cub3d.rotspeed);
		cubdata->cub3d.oldplanx =  cubdata->cub3d.planx;
		cubdata->cub3d.planx =  cubdata->cub3d.planx * cos(cubdata->cub3d.rotspeed) -  cubdata->cub3d.plany * sin( cubdata->cub3d.rotspeed);
		cubdata->cub3d.plany =  cubdata->cub3d.oldplanx * sin(cubdata->cub3d.rotspeed) + cubdata->cub3d.plany * cos(cubdata->cub3d.rotspeed);
	}
	if (keycode == exit_)
		exit(1);
	mlx_clear_window(cubdata->cub3d.connection, cubdata->cub3d.window);
	mlx_destroy_image(cubdata->cub3d.connection, cubdata->cub3d.img.image_ptr);
	cubdata->cub3d.img.image_ptr = mlx_new_image(cubdata->cub3d.connection, cubdata->rx, cubdata->ry);
	cubdata->cub3d.img.data = (int*)mlx_get_data_addr(cubdata->cub3d.img.image_ptr, &(cubdata->cub3d.img.bpp), &(cubdata->cub3d.img.size), &(cubdata->cub3d.img.endian));
	draw_wall(cubdata);
	mlx_put_image_to_window(cubdata->cub3d.connection, cubdata->cub3d.window, cubdata->cub3d.img.image_ptr, 0, 0);
	return (0);
}

// int draw_screen(t_data *cubdata){
// 	write(1, "hola\n", 5);
// 	mlx_clear_window(cubdata->cub3d.connection, cubdata->cub3d.window);
// 	mlx_destroy_image(cubdata->cub3d.connection, cubdata->cub3d.img.image_ptr);
// 	cubdata->cub3d.img.image_ptr = mlx_new_image(cubdata->cub3d.connection, cubdata->rx, cubdata->ry);
// 	cubdata->cub3d.img.data = (int*)mlx_get_data_addr(cubdata->cub3d.img.image_ptr, &(cubdata->cub3d.img.bpp), &(cubdata->cub3d.img.size), &(cubdata->cub3d.img.endian));
// 	draw_wall(cubdata);
// 	mlx_put_image_to_window(cubdata->cub3d.connection, cubdata->cub3d.window, cubdata->cub3d.img.image_ptr, 0, 0);
// 	return 0;
// }



