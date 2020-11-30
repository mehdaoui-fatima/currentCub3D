#include "../../header/cub3d.h"

int	null_text(char *path)
{
	return ((path != NULL));
}

int	pngend(char *png)
{
	int		len;

	len = ft_strlen(png) - 1; 
	return (png[len] == 'g' && png[len - 1] == 'n' && png[len - 2] == 'p' && png[len - 3] == '.');
}

char	*ft_each_texture(char *path, t_cub3d *cub, char*micub_err[])
{
	int len;
	int fd;
	
	if (null_text(path))
		ft_errors(micub_err[DUP_LINE], micub_err[TEXTURE]);
	if (cub->getl.spaces > 0)
		ft_errors(micub_err[NOSPACESNEEDED], micub_err[TEXTURE]);
	len = ft_len(cub->getl.newline);
	if (len != 2)
		ft_errors(micub_err[NUM_ARG], micub_err[TEXTURE]);
	// path existe or not 
	else if ((fd = open(cub->getl.newline[1], O_RDONLY)) == -1)
		ft_errors(micub_err[INVALID_PATH], micub_err[TEXTURE]);

	path = ft_strdup(cub->getl.newline[1]);
	if (!pngend(path))
		ft_errors(micub_err[EXTENSION], micub_err[MAP_FILE]);
	return (path);
}

void	ft_textures(t_cub3d *cub, char *micub_err[])
{
	
	int len;
	int fd;

	cub->getl.newline = ft_split(cub->getl.line, ' ');
	if (ft_strcmp(cub->getl.newline[0], "NO") == 0)
		cub->tex.north = ft_each_texture(cub->tex.north, cub, micub_err);
	else if (ft_strcmp(cub->getl.newline[0], "SO") == 0)
		cub->tex.south = ft_each_texture(cub->tex.south, cub, micub_err);
	else if (ft_strcmp(cub->getl.newline[0], "WE") == 0)
		cub->tex.west = ft_each_texture(cub->tex.west, cub, micub_err);
	else if (ft_strcmp(cub->getl.newline[0], "EA") == 0)
		cub->tex.east = ft_each_texture(cub->tex.east, cub, micub_err);
	else if (ft_strcmp(cub->getl.newline[0], "S") == 0)
		cub->tex.sprite = ft_each_texture(cub->tex.sprite, cub, micub_err);
	else
		ft_errors(micub_err[INVALID_LINE], micub_err[TEXTURE]);
	ft_free(cub->getl.newline); // make sure of this 
	
}
