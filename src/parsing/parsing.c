#include "../../header/cub3d.h"

char *(micub_err[]) =
{
	"Unexpected number of arguments, ",
 	"Duplicate line, ",
	"Must contain only integers, ",
	"Incorrect Line, ",
	"RGB format not correct, values must be in the 0..255 range, ",
	"Open image failed. path is not correct, ",
	"Width and Height must be non-negative, ",
	"Resolution",
	"Texture path",
	"Map file",
	"Ceiling",
	"Floor",
	"Missing values,",
	"Imposter line, ",
	"No spaces needed at the start of the line, ",
	"Invalid map, ",
	"Map",
	"Only one of the characters N,S,E or W is needed for the player’s start position, ",
	"Invalid extension .png required, ",
	"Invalid extension fileName.cub required, ",
};


void initializedata(t_cub3d *cub)
{
	cub->res.rx = -1;
	cub->res.ry = -1;
	cub->rgb.cr = -1;
	cub->rgb.cg = -1;
	cub->rgb.cb = -1;
	cub->rgb.fr = -1;
	cub->rgb.fg = -1;
	cub->rgb.fb = -1;
	cub->tex.north = NULL;
	cub->tex.east = NULL;
	cub->tex.west = NULL;
	cub->tex.south = NULL;
	cub->tex.sprite = NULL;
	cub->maps.map_len = 0;
	cub->posx = -1;
	cub->posy = -1;
	cub->numsprites = 0;
}


int	fileend(char *argv)
{
	int		arg;

	arg = ft_strlen(argv) - 1; 
	return (argv[arg] == 'b' && argv[arg - 1] == 'u' && argv[arg - 2] == 'c' && argv[arg - 3] == '.');
}

t_cub3d *parsing(t_cub3d *cub, char *argv)
{
	char	r;


	if (!fileend(argv))
		ft_errors(micub_err[FILE],micub_err[MAP_FILE]);
	if ((cub->getl.fd = open(argv, O_RDONLY)) < 0)
	{
		ft_putendl_fd("Error\n", 1);
		perror(strerror(errno));
		exit(0);
	}
	initializedata(cub);
	while ((cub->getl.r = get_next_line(cub->getl.fd,&(cub->getl.line))) == 1)
	{
		if (strcmp(cub->getl.line, "\0") == 0)
		{
			free(cub->getl.line);
			cub->getl.line = NULL;
			continue;
		}
			
		cub->getl.spaces = ft_spaces(cub); // 0 or index
		//printf("--%d--\n",cub->spaces);
		r = cub->getl.line[cub->getl.spaces];
		if (r == 'R')
			resolution(cub, micub_err);
		else if (r == 'F' || r == 'C')
			ft_ceil_floor(cub, micub_err);
		else if (r == 'N' || r == 'S' || r == 'W' || r == 'E')
			ft_textures(cub, micub_err);
		else if  (r == '1')
		{
			ft_map(cub, micub_err);
		}	
		else
		{
			//printf("|%s|\n",cub->line);
			ft_errors (micub_err[IMPOSTER], micub_err[MAP_FILE]);
		}
		free(cub->getl.line);
		//printf("%c\n",r);
			
	}//only one line left befor EOF 
	 if (!ft_missingdata(cub) || !cub->maps.map)
	 	ft_errors (micub_err[MISSING], micub_err[MAP_FILE]);
	// printf("\n\nrx:%lld\n\nry:%lld\n\n", cub->rx, cub->ry);
	// printf("Floor\nr:%d\n\ng:%d\n\nb:%d\n\n", cub->fr, cub->fg, cub->fb);
	// printf("Ceiling\nr:%d\n\ng:%d\n\nb:%d\n\n", cub->cr, cub->cg, cub->cb);
	// printf("north:%s\n\neast:%s\n\nsouth:%s\n\nwest:%s\n\nsprite:%s", cub->north,cub->east,
	//  cub->south, cub->west,cub->sprite);
	return (cub);
}
