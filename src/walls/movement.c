#include "../../header/cub3d.h"

int ft_key_press(int keycode, t_cub3d *cub)
{
//	printf("%d",keycode);
	if (cub->movespeed > 1)
		cub->movespeed *= 0.1;
	if (keycode == move_right)
	{
		if(cub->maps.worldMap[(int)(cub->posx + cub->planx * cub->movespeed)][(int)(cub->posy)] == 0) 
			cub->posx += cub->planx * cub->movespeed;
		if(cub->maps.worldMap[(int)(cub->posx)][(int)(cub->posy + cub->plany* cub->movespeed)] == 0)
		cub->posy += cub->plany* cub->movespeed;
	}
	if (keycode == move_left)
	{
		if(cub->maps.worldMap[(int)(cub->posx - cub->planx * cub->movespeed)][(int)(cub->posy)] == 0) 
			cub->posx -= cub->planx * cub->movespeed;
		if(cub->maps.worldMap[(int)(cub->posx)][(int)(cub->posy - cub->plany* cub->movespeed)] == 0)
			cub->posy -= cub->plany* cub->movespeed;
	}
	if (keycode == move_towards)
	{
		if(cub->maps.worldMap[(int)(cub->posx + cub->dirx * cub->movespeed)][(int)(cub->posy)] == 0) 
			cub->posx += cub->dirx * cub->movespeed;
		if(cub->maps.worldMap[(int)(cub->posx)][(int)(cub->posy + cub->diry * cub->movespeed)] == 0)
		cub->posy += cub->diry * cub->movespeed;
	}
	if (keycode == move_backwards)
	{
		if(cub->maps.worldMap[(int)(cub->posx - cub->dirx * cub->movespeed)][(int)(cub->posy)] == 0)
			cub->posx -= cub->dirx * cub->movespeed;
		if(cub->maps.worldMap[(int)(cub->posx)][(int)(cub->posy - cub->diry * cub->movespeed)] == 0)
			cub->posy -= cub->diry * cub->movespeed;
	}
	if (keycode == rot_right)
	{
		cub->olddirx = cub->dirx;
		cub->dirx = cub->dirx * cos(-cub->rotspeed) - cub->diry * sin(-cub->rotspeed);
		cub->diry = cub->olddirx * sin(-cub->rotspeed) + cub->diry * cos(-cub->rotspeed);
		cub->oldplanx = cub->planx;
		cub->planx = cub->planx * cos(-cub->rotspeed) - cub->plany * sin(-cub->rotspeed);
		cub->plany = cub->oldplanx * sin(-cub->rotspeed) + cub->plany * cos(cub->rotspeed);
	}
	if (keycode == rot_left)
	{
		cub->olddirx =  cub->dirx;
		cub->dirx =  cub->dirx * cos( cub->rotspeed) -  cub->diry * sin( cub->rotspeed);
		cub->diry =  cub->olddirx * sin(cub->rotspeed) +  cub->diry * cos( cub->rotspeed);
		cub->oldplanx =  cub->planx;
		cub->planx =  cub->planx * cos(cub->rotspeed) -  cub->plany * sin( cub->rotspeed);
		cub->plany =  cub->oldplanx * sin(cub->rotspeed) + cub->plany * cos(cub->rotspeed);
	}
	if (keycode == exit_)
		exit(1);
	mlx_clear_window(cub->connection, cub->window);
	mlx_destroy_image(cub->connection, cub->img.image_ptr);
	cub->img.image_ptr = mlx_new_image(cub->connection, cub->res.rx, cub->res.ry);
	cub->img.data = (int*)mlx_get_data_addr(cub->img.image_ptr, &(cub->img.bpp), &(cub->img.size), &(cub->img.endian));
	draw_wall(cub);
	mlx_put_image_to_window(cub->connection, cub->window, cub->img.image_ptr, 0, 0);
	return (0);
}