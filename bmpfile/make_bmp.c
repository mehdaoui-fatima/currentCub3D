

#include "bmp.h"

static t_bmp	init_bmph(t_cub3d *cub)
{
	t_bmp		res;

	res.id[0] = 'B';
	res.id[1] = 'M';
	res.file_size = 54 + 4 * (int)cub->res.rx * (int)cub->res.ry;
	res.unused = 0;
	res.offset = 54;
	res.dib = 54 - 14;
	res.width = (int)cub->res.rx;
	res.height = -(int)cub->res.ry;
	res.plane[0] = 1;
	res.plane[1] = 0;
	res.bpp[0] = 32;
	res.bpp[1] = 0;
	res.compression = 0;
	res.raw_bitmap_size = 4 * (int)cub->res.rx * (int)cub->res.ry;
	res.resx = 0;
	res.resy = 0;
	res.number_of_colors = 0;
	res.important_colors = 0;
	return (res);
}

void			make_bmp(t_cub3d *cub)
{
	t_bmp		img;
	int			file;

	file = open("./cub3d.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0666);
	img = init_bmph(cub);
	write(file, &img, 54);
	write(file, cub->img.data, img.raw_bitmap_size);
	close(file);
	exit(0);
}
