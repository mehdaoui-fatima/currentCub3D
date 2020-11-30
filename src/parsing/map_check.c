
#include "../../header/cub3d.h"


void first_last_line(char *first, char *last, char *micub_err[])
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(first[i] || last[j])
	{
		if (first[i])
		{
			if (first[i] != '1' && first[i] != ' ')
			{
				printf("first line map here\n");
		        ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
			}
			i++;
		}
		else if (last[j])
		{
			if (last[j] != '1' && last[j] != ' ')
				{
					printf("last line map here\n");
					ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
				}
			j++;
		}
	}
}

void	ft_borders(char c1, char c2, char *micub_err[])
{
	if (c1 != '1' || c2 != '1')
	{

		printf("--+-+-+-+-+-+-+here|%c|%c|\n",c1,c2);
		ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
	}
		
}

int	ft_surrounded(char a, char b, char c , char d)
{
	return((a == '1' || a == ' ') && (b == '1' || b == ' ') && (c == '1' || c == ' ') && (d == '1' || d == ' '));
}

double *create_dir_plan(double a, double b, double c, double d)
{
	double *tab;

	tab = (double*)malloc(sizeof(double) * 4);
	tab[0] = a;
	tab[1] = b;
	tab[2] = c;
	tab[3] = d;
	return (tab);
}

void ft_dir_plan(t_cub3d *cub, double *tab)
{
	cub->dirx  = tab[0];
	cub->diry  = tab[1];
	cub->planx = tab[2];
	cub->plany = tab[3];
	free(tab);
	//printf("-----|%f|%f|%f|%f-----\n\n\n",cub->cub3d.dirx ,
	//cub->cub3d.diry,cub->cub3d.planx,cub->cub3d.plany);
}

int ft_each_map_line(char *str, int index, t_cub3d *cub, char *micub_err[])
{
	//cub->sprite[0] = {x,y} ex
	int tab[4];
	int i = -1;
	int j = 0;

	while(str[++i])
	{
		//printf("%d\n",index);
		if (str[i] != '2' && str[i] != '1' && str[i] != ' ' && str[i] != '0' &&
		str[i] != 'N' && str[i] != 'W' && str[i] != 'E' && str[i] != 'S')
		{
			//printf("ft_each_line: thats why i failed|%c|\n",str[i]);
			return (0);// failed
		}
		if (str[i] == 'N' || str[i] == 'W' || str[i] == 'E' || str[i] == 'S')
		{
			if (cub->posy != -1)
				ft_errors(micub_err[DIR], micub_err[MAP]);
			cub->posx = index + 0.1; // to avoid spawn in the wall 0.5 should be added
			cub->posy = i + 0.1;
			printf("\n\n from parsing:  posx:%f,posy:%f\n\n",cub->posx,cub->posy);
			//printf("\n\n\nft_each line %f %f\n\n\n",cub->cub3d.posy,cub->cub3d.posx);
			if (str[i] == 'N')
				ft_dir_plan(cub, create_dir_plan(-1,0,0,0.66));
			else if (str[i] == 'S')
				ft_dir_plan(cub, create_dir_plan(1,0,0,-0.66));
			else if (str[i] == 'W')
				ft_dir_plan(cub, create_dir_plan(0,-1,-0.66,0));
			else if (str[i] == 'E')
				ft_dir_plan(cub, create_dir_plan(0,1,0.66,0));
		}
		if (str[i] == '2')
			cub->numsprites++;
	}
	return (1);
}


void	ft_mapvalid(t_cub3d *cub, char *micub_err[])
{
	
	int i;
	int j;
	int	len;
	char *str;
	int len_j;
	int len_i;
	char a;
	char b;
	char c;
	char d;
	int len_next;
	int len_previous;

	i = -1;
	a = '1';
	b = '1';
	c = '1';
	d = '1';
	
	if (cub->maps.index < 2 )
	{
		printf("++++++++++here index %d\n",cub->maps.index);
		ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
	}
		//ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
	first_last_line(cub->maps.new_map[0], cub->maps.new_map[cub->maps.index], micub_err);
	while(cub->maps.new_map[++i]) 
	{
		//printf("|%s|\n",cub->new_map[i]);
		str = ft_strtrim(cub->maps.new_map[i], " ");
		if (!ft_each_map_line(cub->maps.new_map[i], i, cub, micub_err)) // only numbers
		{
			printf("----->>>>>>here\n");
			ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
		}
		len = ft_strlen(str) - 1;
		ft_borders(str[0], str[len], micub_err);
		len_j =  ft_strlen(cub->maps.new_map[i]) - 1;
		len_i = cub->maps.index;
		j = 0;
		//printf("|%s|i=%d|j=%d|\n",cub->new_map[i],len_i,len_j);
		while(cub->maps.new_map[i][j]) // 3 lines
		{
			if (cub->maps.new_map[i][j] == ' ')
			{
				if (0 <= j - 1  && j - 1 <= len_j)
					a = cub->maps.new_map[i][j - 1];
				if (0 <= j + 1 && j + 1 <= len_j)
					c = cub->maps.new_map[i][j + 1];
				if (0 <= i - 1 && i-1  <= len_i )
				{
					len_previous = ft_strlen(cub->maps.new_map[i - 1]) - 1;
					if (len_previous < j)
						b = '1';
					else 
						b = cub->maps.new_map[i - 1][j];
				}
				if (0 <= i + 1 && i + 1 <= len_i) // line exists
				{
					len_next= ft_strlen(cub->maps.new_map[i+1]) - 1;
					if (len_next < j)
						d = '1';
					else
						d = cub->maps.new_map[i + 1][j];
				}
				if (!ft_surrounded(a,b,c,d))
				{
					printf("----here\n");
					
					ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
				}	
			}
			j++;
		}
	}
	printf("\n----num sprite:%d\n",cub->numsprites);
	cub->zbuffer = (double*)malloc(sizeof(double) * cub->res.rx);
	cub->sprites = (t_sprite*)malloc(sizeof(t_sprite) * cub->numsprites);
	ft_create_worldMap(cub);
}

