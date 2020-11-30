#include "../../header/cub3d.h"


int	ft_missingdata(t_cub3d *cub)
{
	return (
		(cub->res.rx != -1 && cub->res.ry != -1) &&
		(cub->rgb.cr != -1 && cub->rgb.cg != -1 && cub->rgb.cb != -1) &&
		(cub->rgb.fr != -1 && cub->rgb.fg != -1 && cub->rgb.fb != -1) &&
		(cub->tex.north != NULL && cub->tex.south != NULL && 
		cub->tex.west != NULL && cub->tex.east != NULL && cub->tex.sprite != NULL)
	);
	//1 not missing
	//0 missing 
}


void	ft_addrow(t_cub3d *cub)
{
	int res;
	cub->maps.tmp = (char**)malloc((cub->maps.map_len = ft_len(cub->maps.map) + 2)*sizeof(char*));
	cub->maps.index = -1;
	//printf("map_len%d\n",cub->map_len);
	while(cub->maps.map[++cub->maps.index]) //0
	{
		cub->maps.tmp[cub->maps.index] = ft_strdup(cub->maps.map[cub->maps.index]);
	}
	cub->maps.tmp[cub->maps.index] = ft_strdup(cub->getl.line);
	cub->maps.tmp[cub->maps.index + 1] = NULL;
	cub->maps.max_len = (cub->maps.max_len < (res = ft_strlen(cub->getl.line))) ? res : cub->maps.max_len;
	printf("%d\n\n\n",ft_len(cub->maps.map));
	// int k = 0;
	// while(cub->maps.map[k])
	// {
	// 	printf("|%s|\n",cub->maps.map[k]);
	// 	k++;
	// }
	// printf("vefore free %p\n%p\n",cub->maps.map,cub->maps.tmp);
	ft_free(cub->maps.map);
	cub->maps.map = cub->maps.tmp;
	printf("after free %p\n%p\n",cub->maps.map,cub->maps.tmp);
	free(cub->getl.line);	
	cub->getl.line = NULL;
	//printf("*********%d******\n");
}

void	ft_map(t_cub3d *cub, char *micub_err[])
{
	
	int true;
	int i;
	
	true = 1;

	i = 3;
	//printf("ft_map() called\n%s",cub->line);
	if (!ft_missingdata(cub))
	{
		//printf("missing data %d",ft_missingdata(cub));
		ft_errors (micub_err[INVALID_LINE], micub_err[MAP_FILE]);
	}	
	if (true)
	{
		cub->maps.map = (char **)malloc(2 * sizeof(char *));
		cub->maps.map[0] = ft_strdup(cub->getl.line);
		cub->maps.max_len = ft_strlen(cub->getl.line);
		//printf("--------%d---------\n",cub->max_len);
		cub->maps.map[1] = NULL;
		true = 0;
		//printf("|%s|\n",cub->line);
		free(cub->getl.line);
	}
	while ((cub->getl.r = get_next_line(cub->getl.fd, &(cub->getl.line))) == 1)
	{
		//printf("-- %s --\n", cub->getl.line);
		ft_addrow(cub);
		// if (cub->line)
		// 	free(cub->line);
		// while (i == 3)
		// {
		// 	free(cub->line);
		// 	cub->line = NULL;
		// 	i = 2;
		// }
			
		//printf("|%s|\n",cub->line);
		//cub->line = NULL;
		//free(cub->getl.line);
		
		//cub->getl.line = NULL;
	}	
	ft_addrow(cub);
	//free(cub->line);
	ft_new_map(cub);
	ft_mapvalid(cub, micub_err);
	// missing values in map should be in a function
	if (cub->posy == -1)
		ft_errors(micub_err[MISSING],micub_err[MAP]);
	// is there any missing values in map?
	//ft_free(cub->map);
}