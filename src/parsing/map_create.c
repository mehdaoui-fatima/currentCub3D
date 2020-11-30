#include "../../header/cub3d.h"

void	ft_new_map(t_cub3d *cub)
{
	int i = -1;
	int len;
	char *s;

	cub->maps.new_map = (char**)malloc(sizeof(char*) * (cub->maps.index + 2));
	cub->maps.new_map[cub->maps.index + 1]  =  NULL;
	while (cub->maps.map[++i])
	{
		len = ft_strlen(cub->maps.map[i]);
		s = (char*)malloc(sizeof(char) * (cub->maps.max_len - len + 1));
		s[cub->maps.max_len - len ] = '\0';
		ft_memset(s,32,cub->maps.max_len - len);
		cub->maps.new_map[i] =  ft_strjoin(cub->maps.map[i],s);
		free(s);
		free(cub->maps.map[i]);
	}
	ft_free(cub->maps.map);
}


void	ft_create_worldMap(t_cub3d *cub)
{
	//printf("|%c|\n",cub->maps.new_map[0][0]);
	int i;
	int j;
	int k;
	int len;

	i = -1;
	k = 0;
	cub->maps.worldMap = (int**)malloc(sizeof(int*) * (cub->maps.index + 1));
	//printf("\n\n\n%d\n\n\n",cub->index);
	while(cub->maps.new_map[++i])
	{
		cub->maps.worldMap[i] = (int*)malloc(sizeof(int) * cub->maps.max_len);
		j = -1;
		while(cub->maps.new_map[i][++j])
		{
			if (cub->maps.new_map[i][j] == '2')
			{
				cub->sprites[k].x = i + 0.5;
				cub->sprites[k].y = j + 0.5;
			//	printf("\nposx:%d posy:%d\n",cub->sprites[k].x, cub->sprites[k].y);
				k++;
			}
			if (cub->maps.new_map[i][j] == ' ')
				cub->maps.worldMap[i][j] = 1;
			else if (ft_isalpha((int)cub->maps.new_map[i][j]))
				cub->maps.worldMap[i][j] = 0;
			else 
				cub->maps.worldMap[i][j] = cub->maps.new_map[i][j] - '0';
			//printf("%d",cub->worldMap[i][j]);
		}
		//printf("|");
	}
	//printf("\n\n%d\n\n",ft_len(cub->maps.new_map));
	ft_free(cub->maps.new_map);
	//printf("\n\n%d\n\n",ft_len(cub->maps.new_map));
	//printf("%d ",i);
}


