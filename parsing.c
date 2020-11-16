#include "cub3d.h"

#define MAX_WIDTH 2560
#define MAX_HEIGHT 1440

#define NUM_ARG 0
#define DUP_LINE 1
#define WRONG_DATA 2
#define INVALID_LINE 3
#define INVALID_RGB 4
#define INVALID_PATH 5
#define NON_NEGATIVE 6
#define RESOLUTION 7
#define TEXTURE 8
#define MAP_FILE 9
#define CEILING 10
#define FLOOR 11
#define MISSING 12
#define IMPOSTER 13
#define NOSPACESNEEDED 14
#define INVALID_MAP 15
#define MAP 16

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
	"Map"
};

void initializedata(t_data *cubdata)
{
	cubdata->rx = -1;
	cubdata->ry = -1;
	cubdata->cr = -1;
	cubdata->cg = -1;
	cubdata->cb = -1;
	cubdata->fr = -1;
	cubdata->fg = -1;
	cubdata->fb = -1; 
	cubdata->res = 0;// no idea
	cubdata->north = NULL;
	cubdata->east = NULL;
	cubdata->west = NULL;
	cubdata->south = NULL;
	cubdata->sprite = NULL;
	cubdata->map_len = 0;
}

int	ft_spaces(t_data *cubdata)
{
	cubdata->spaces = 0;
	while(cubdata->line[cubdata->spaces] == ' ')
		cubdata->spaces++;
	return(cubdata->spaces);
}

int ft_len(char **newline)
{

	int i = 0;

	if (!newline)
		return (0);
	while(newline[i])
		i++;
	return(i);
}

int ft_isnumber(char *s)
{
    int i;
    i = 0;
	if (s[i] == '-')
		i++;
    while(s[i])
    {
        if (!ft_isdigit(s[i]))
            return (0);//is not number
        i++;
    }
    return(1);//is number
}

void	ft_errors(char *error, char *str)
{
	ft_putendl_fd("Error\n", 1);
	ft_putstr_fd(error, 1);
	ft_putstr_fd(str, 1);
	exit(0);
}

// resolution **************************************************
void	resolution(t_data *cubdata)
{
	cubdata->newline = ft_split(cubdata->line, ' ');
	if (ft_strcmp(cubdata->newline[0], "R") == 0)
	{
		if (cubdata->spaces > 0)
			ft_errors(micub_err[NOSPACESNEEDED], micub_err[RESOLUTION]);
		cubdata->res = ft_len(cubdata->newline);
		if (cubdata->res != 3)
			ft_errors(micub_err[NUM_ARG], micub_err[RESOLUTION]);
		else if(cubdata->rx != -1)
			ft_errors(micub_err[DUP_LINE], micub_err[RESOLUTION]);
		else if (!(ft_isnumber(cubdata->newline[1]) 
				&& ft_isnumber(cubdata->newline[2])))
		ft_errors(micub_err[WRONG_DATA], micub_err[RESOLUTION]);
		else 
		{
			if (cubdata->newline[1][0] == '-' || cubdata->newline[2][0] == '-')
				ft_errors(micub_err[NON_NEGATIVE], micub_err[RESOLUTION]);
			cubdata->rx = ft_atoi(cubdata->newline[1]);
			cubdata->ry = ft_atoi(cubdata->newline[2]);
			cubdata->rx = (cubdata->rx > MAX_WIDTH || cubdata->rx <= 0) ? MAX_WIDTH : cubdata->rx;
			cubdata->ry = (cubdata->ry > MAX_HEIGHT || cubdata->ry <= 0) ? MAX_HEIGHT : cubdata->ry;
		}
	}
	else
		ft_errors(micub_err[INVALID_LINE], micub_err[RESOLUTION]);
}

// ceiling floor  **************************************************
int	ft_check_commas(char *line)
{
	int i;
	
	i = 0;
	while(line[i] && line[i + 1])
	{
		if (line[i] == ',' && line[i + 1] == ',')
			 return (1);// followed commas detected
		i++;
	}
	if(line[i] == ',' || line[0] == ',')
		return (1);
	return (0);
}

void	ft_each_color(int *r, int *g, int *b, t_data *cubdata)
{
	if (*r != -1)
		ft_errors(micub_err[DUP_LINE], micub_err[cubdata->err]);
	*r = ft_atoi(cubdata->new[0]);
	*g = ft_atoi(cubdata->new[1]);
	*b = ft_atoi(cubdata->new[2]);
	if (!((*r >= 0 && *r <= 255) && (*g >= 0 && *g <= 255) && (*b >= 0 && *b <= 255)))
		ft_errors(micub_err[INVALID_RGB], micub_err[cubdata->err]);
}

void    ft_ceil_floor(t_data *cubdata)
{
    int		len1;
    int		len2;

    cubdata->newline = ft_split(cubdata->line, ' ');
    cubdata->new= ft_split(cubdata->newline[1], ',');
    len1 = ft_len(cubdata->newline);
    len2 = ft_len(cubdata->new);
	if ((ft_strcmp(cubdata->newline[0], "C") == 0) || (ft_strcmp(cubdata->newline[0], "F") == 0))
	{
		cubdata->err = (cubdata->newline[0][0] == 'C') ? CEILING : FLOOR;
		if (cubdata->spaces > 0)
			ft_errors(micub_err[NOSPACESNEEDED], micub_err[cubdata->err]);
		if (len1 != 2 || len2 != 3)
			ft_errors(micub_err[NUM_ARG], micub_err[cubdata->err]);
		else if (!(ft_isnumber(cubdata->new[0]) && ft_isnumber(cubdata->new[1]) && ft_isnumber(cubdata->new[2])))
			ft_errors(micub_err[INVALID_RGB], micub_err[cubdata->err]);
		else if (ft_check_commas(cubdata->newline[1]))
			ft_errors(micub_err[INVALID_RGB], micub_err[cubdata->err]);
		else if (cubdata->err == CEILING)
			ft_each_color(&cubdata->cr, &cubdata->cg, &cubdata->cb, cubdata); 
		else if (cubdata->err == FLOOR)
			ft_each_color(&cubdata->fr, &cubdata->fg, &cubdata->fb, cubdata);
	}
	else
		ft_errors(micub_err[INVALID_LINE], micub_err[MAP_FILE]);

}

// texture  **************************************************
int	null_text(char *path)
{
	return ((path != NULL));
}

char	*ft_each_texture(char *path, t_data *cubdata)
{
	int len;
	int fd;
	
	if (null_text(path))
		ft_errors(micub_err[DUP_LINE], micub_err[TEXTURE]);
	if (cubdata->spaces > 0)
		ft_errors(micub_err[NOSPACESNEEDED], micub_err[TEXTURE]);
	len = ft_len(cubdata->newline);
	if (len != 2)
		ft_errors(micub_err[NUM_ARG], micub_err[TEXTURE]);
	// path existe or not 
	else if ((fd = open(cubdata->newline[1], O_RDONLY)) == -1)
		ft_errors(micub_err[INVALID_PATH], micub_err[TEXTURE]);

	path = cubdata->newline[1];
	return (path);
}

void	ft_textures(t_data *cubdata)
{
	
	int len;
	int fd;

	cubdata->newline = ft_split(cubdata->line, ' ');
	if (ft_strcmp(cubdata->newline[0], "NO") == 0)
		cubdata->north = ft_each_texture(cubdata->north, cubdata);
	else if (ft_strcmp(cubdata->newline[0], "SO") == 0)
		cubdata->south = ft_each_texture(cubdata->south, cubdata);
	else if (ft_strcmp(cubdata->newline[0], "WE") == 0)
		cubdata->west = ft_each_texture(cubdata->west, cubdata);
	else if (ft_strcmp(cubdata->newline[0], "EA") == 0)
		cubdata->east = ft_each_texture(cubdata->east, cubdata);
	else if (ft_strcmp(cubdata->newline[0], "S") == 0)
		cubdata->sprite = ft_each_texture(cubdata->sprite, cubdata);
	else
		ft_errors(micub_err[INVALID_LINE], micub_err[TEXTURE]);

}



// map valid **********************************

//TODO you were here
void	ft_add_zero(char *str, int len_added, int len)
{
	printf("|%s|%d|\n",str,len_added);
	while(len < len_added)
	{
		str[len]

		len++;
	}


}


void	ft_new_map(t_data *cubdata)
{
	//cubdata->max_len;
	//cubdata->index + 1;
	int i = -1;
	char **new_map;
	int len;

	new_map = (char**)malloc((cubdata->index + 2) * sizeof(char*));
	new_map[cubdata->index] = NULL;
	while (++i <= cubdata->index)
	{
		new_map[i] =  ft_strdup(cubdata->map[i]);
		len = ft_strlen(new_map[i]);
		ft_add_zero(new_map[i],cubdata->max_len - len, len);
		
	}
//	printf("%d------------\n\n\n\n\n\n",cubdata->index);
}

void first_last_line(char *first, char *last)
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
				ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
			i++;
		}
		else if (last[j])
		{
			if (last[j] != '1' && last[j] != ' ')
				ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
			j++;
		}
	}
}


void	ft_borders(char c1, char c2)
{
	//printf("ft_borders here |%c|%c|\n",c1,c2);
	if (c1 != '1' || c2 != '1')
		ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
}



int	ft_surrounded(char a, char b, char c , char d)
{
	// printf("  |%c| \n",b);
	// printf("|%c| ",a);
	// printf("|%c|\n",c);
	// printf("  |%c| \n\n",d);
	return((a == '1' || a == ' ') && (b == '1' || b == ' ') && (c == '1' || c == ' ') && (d == '1' || d == ' '));
}

int ft_each_map_line(char *str)
{
	//printf("\nhere|%s|\n",str);
	int i = -1;
	while(str[++i])
	{
		if ((str[i] < '0' ||  str[i] > '9') && str[i] != ' ' && str[i] != '2')
		{
			printf("ft_each_line: thats why o failed|%c|\n",str[i]);
			return (0);
		}//failed
	}
	return (1);
}


void	ft_mapvalid(t_data *cubdata)
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
	// if (cubdata->index < 3)
	// 	ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
	first_last_line(cubdata->map[0], cubdata->map[cubdata->index]);
	while(cubdata->map[++i]) 
	{
		
		str = ft_strtrim(cubdata->map[i], " ");
		if (!ft_each_map_line(cubdata->map[i])) // only numbers
			ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
		len = ft_strlen(str) - 1;
		ft_borders(str[0], str[len]);
		len_j =  ft_strlen(cubdata->map[i]) - 1;
		len_i = cubdata->index;
		j = 0;
		//printf("|%s|i=%d|j=%d|\n",cubdata->map[i],len_i,len_j);
		while(cubdata->map[i][j]) // 3 lines
		{
			if (cubdata->map[i][j] == ' ')
			{
				if (0 <= j - 1  && j - 1 <= len_j)
					a = cubdata->map[i][j - 1];
				if (0 <= j + 1 && j + 1 <= len_j)
					c = cubdata->map[i][j + 1];
				if (0 <= i - 1 && i-1  <= len_i )
				{
					len_previous = ft_strlen(cubdata->map[i - 1]) - 1;
					if (len_previous < j)
						b = '1';
					else 
						b = cubdata->map[i - 1][j];
				}
				if (0 <= i + 1 && i + 1 <= len_i) // line exists
				{
					len_next= ft_strlen(cubdata->map[i+1]) - 1;
					if (len_next < j)
						d = '1';
					else
						d = cubdata->map[i + 1][j];
				}
				if (!ft_surrounded(a,b,c,d))
					ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
			}
			j++;
		}
	}
}


// map ******************************************************

int	ft_missingdata(t_data *cubdata)
{
	return (
		(cubdata->rx != -1 && cubdata->ry != -1) &&
		(cubdata->cr != -1 && cubdata->cg != -1 && cubdata->cb != -1) &&
		(cubdata->fr != -1 && cubdata->fg != -1 && cubdata->fb != -1) &&
		(cubdata->north != NULL && cubdata->south != NULL && 
		cubdata->west != NULL && cubdata->east != NULL && cubdata->sprite != NULL)
	);
	//1 not missing
	//0 missing 
}

void	ft_clear(char **tmp)
{
	int i;

	i = 0;
	while(tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	tmp = NULL;
}

void	ft_addrow(char **tmp, t_data *cubdata)
{
	int res;

	tmp = (char**)malloc((cubdata->map_len = ft_len(cubdata->map) + 2)*sizeof(char*));
	cubdata->index = -1;
	//printf("map_len%d\n",cubdata->map_len);
	while(cubdata->map[++cubdata->index]) //0
		tmp[cubdata->index] = cubdata->map[cubdata->index];
	tmp[cubdata->index] = cubdata->line;
	tmp[cubdata->index + 1] = NULL;
	cubdata->max_len = (cubdata->max_len < (res = ft_strlen(cubdata->line))) ? res : cubdata->max_len;
	//printf("********%d*******\n",cubdata->max_len);
	free(cubdata->map);
	cubdata->map = tmp;
}


void	ft_map(t_data *cubdata)
{
	char **tmp;
	int true;
	
	true = 1;

	//printf("ft_map() called\n%s",cubdata->line);
	if (!ft_missingdata(cubdata))
	{
		//printf("missing data %d",ft_missingdata(cubdata));
		ft_errors (micub_err[INVALID_LINE], micub_err[MAP_FILE]);
	}	
	if (true)
	{
		cubdata->map = (char **)malloc(2 * sizeof(char *));
		cubdata->map[0] = ft_strdup(cubdata->line);
		cubdata->max_len = ft_strlen(cubdata->line);
		//printf("--------%d---------\n",cubdata->max_len);
		cubdata->map[1] = NULL;
		true = 0;
	}
	while ((cubdata->r = get_next_line(cubdata->fd,&(cubdata->line))) == 1)
		ft_addrow(tmp, cubdata);
	ft_addrow(tmp, cubdata);
	ft_new_map(cubdata);
	ft_mapvalid(cubdata);
}






// parsing  **************************************************




t_data *parsing(t_data *cubdata, char *argv)
{
	char	r;
	
	if ((cubdata->fd = open(argv, O_RDONLY)) < 0)
	{
		perror(strerror(errno));
		exit(0);
	}
	initializedata(cubdata);
	while ((cubdata->r = get_next_line(cubdata->fd,&(cubdata->line))) == 1)
	{
		if (strcmp(cubdata->line, "\0") == 0)
			continue;
		cubdata->spaces = ft_spaces(cubdata); // 0 or index
		//printf("--%d--\n",cubdata->spaces);
		r = cubdata->line[cubdata->spaces];
		if (r == 'R')
			resolution(cubdata);
		else if (r == 'F' || r == 'C')
			ft_ceil_floor(cubdata);
		else if (r == 'N' || r == 'S' || r == 'W' || r == 'E')
			ft_textures(cubdata);
		else if  (r == '1')
		{
			ft_map(cubdata);
		}			
		else
		{
			//printf("|%s|\n",cubdata->line);
			ft_errors (micub_err[IMPOSTER], micub_err[MAP_FILE]);
		}
		//printf("%c\n",r);
			
	}//only one line left befor EOF 
	 if (!ft_missingdata(cubdata) || !cubdata->map)
	 	ft_errors (micub_err[MISSING], micub_err[MAP_FILE]);
	// {
	// 	printf("%s",cubdata->map);
	// 	ft_errors (micub_err[INVALID_LINE], micub_err[MAP_FILE]);
	// }	
	//TODO map should contain more than 3 lines 



	printf("\n\nrx:%lld\n\nry:%lld\n\n", cubdata->rx, cubdata->ry);
	printf("Floor\nr:%d\n\ng:%d\n\nb:%d\n\n", cubdata->fr, cubdata->fg, cubdata->fb);
	printf("Ceiling\nr:%d\n\ng:%d\n\nb:%d\n\n", cubdata->cr, cubdata->cg, cubdata->cb);
	printf("north:%s\n\neast:%s\n\nsouth:%s\n\nwest:%s\n\nsprite:%s", cubdata->north,cubdata->east,
	 cubdata->south, cubdata->west,cubdata->sprite);

// int k = 0;	
// 	while(cubdata->map[k])
// 	{
// 		printf("-%d|%s|\n",k,cubdata->map[k]);
// 		k++;
// 	}	


	return (cubdata);
}


//TODO element missing map or line
//TODO path exist, affected to the wrong variable
//

// if (r == ' ' || r == '1')
	// {
	// 	ft_map(cubdata);
	// }	
	//printf("-|%s %d|\n",cubdata->line,cubdata->r); last line here with return 0
	// last thing should be else if ----- line empty
	




	// int k = -1;
	// while(cubdata->map[++k])
	// {
	// 	printf("|%s|%d",cubdata->map[k],k);
	// }
	




	//printf("%s",cubdata->line);



// right tex for sprite!!!!!

// north 
// east
//south
//west

/* Errors
SwO ./pics/barrel.png
SO./pics/barrel.png
SO ./pics\ /barrel.png
// R 78468 64588
// R  68554685456564564156431256896 5896

*/


// void	ft_ceil_floor(t_data *cubdata)
// {
// 	int len1;
// 	int len2;
// 	int err;

// 	cubdata->newline = ft_split(cubdata->line, ' ');
// 	cubdata-> new= ft_split(cubdata->newline[1], ',');
// 	len1 = ft_len(cubdata->newline);
// 	len2 = ft_len(cubdata->new);
// 	if (len1 != 2 || len2 != 3)
// 		ft_errors("Number of arguments not correct, ", "referenced from ceil/floor");
// 	if(!(ft_isnumber(cubdata->new[0]) && ft_isnumber(cubdata->new[1]) && ft_isnumber(cubdata->new[2]))
// 	|| ft_check(cubdata->line))
// 		ft_errors("RGB format not correct, ", "referenced from ceil/floor");
// 	else if(ft_strcmp(cubdata->newline[0], "C") == 0)
// 	{
// 		cubdata->cr = ft_atoi(cubdata->new[0]);
// 		cubdata->cg = ft_atoi(cubdata->new[1]);
// 		cubdata->cb = ft_atoi(cubdata->new[2]);
// 	}
// 	else
// 	{
// 		cubdata->fr = ft_atoi(cubdata->new[0]);
// 		cubdata->fg = ft_atoi(cubdata->new[1]);
// 		cubdata->fb = ft_atoi(cubdata->new[2]);
// 	}
// 	// + -
// 	// completeed 
// }



// int	textures(t_data *cubdata)
// {

// 	//duplicate line
// 	int res;

// 	res = 0;
// 	if (cubdata->res != 2)
// 		ft_errors("incorrect line");
// 	else
// 	{
// 		if(ft_strcmp(cubdata->newline[0], "NO") == 0)
// 			cubdata->no = ft_strdup(cubdata->newline[1]);
// 		else if(ft_strcmp(cubdata->newline[0], "SO") == 0)
// 			cubdata->so = ft_strdup(cubdata->newline[1]);
// 		else if( ft_strcmp(cubdata->newline[0], "WE") == 0)
// 			cubdata->we = ft_strdup(cubdata->newline[1]);
// 		else if(ft_strcmp(cubdata->newline[0], "EA") == 0)
// 			cubdata->ea = ft_strdup(cubdata->newline[1]);
// 		else if(ft_strcmp(cubdata->newline[0], "S") == 0)
// 			cubdata->s = ft_strdup(cubdata->newline[1]);
// 		res = 1;
// 	//make sure of path 


// 	//free
// 	}
// 	return(res);
// }



// int skips(t_data *cubdata)
// {
// 	int i;

// 	i = 0;
// 	while(cubdata->line[i] && cubdata->line[i] == ' ')
// 		i++;
// 	return(i);
// }

// int skipe(t_data *cubdata)
// {
// 	int i;
// 	int len;

// 	i = ft_strlen(cubdata->line) - 1;
// 	len = i;
// 	while(i >= 0 && cubdata->line[i] == ' ')
// 		i--;
// 	//printf("%d",i);
// 	return(i);
// }



// void	ft_getstr(t_data *cubdata)
// {
// 		int start;
// 		int len;

// 		start = skips(cubdata);
// 		len = skipe(cubdata);
// 		//printf("%d %d\n",start,len);

// 	//printf("%d %d  %c|%s|\n",i, j, cubdata->line[j], ft_substr(cubdata->line, i,j));
// 	//printf("|%d %ld|\n",start,len - start + 1);
		
// 		cubdata->map = ft_strjoin(cubdata->map, ft_substr(cubdata->line, start, len - start + 1));
// 		//printf("%s\n",cubdata->map);


	
// 	//printf("|%d %d|\n",i,j);



// }
// have no idea 


// int	ft_check_space(char *line)
// {
// 	if (line[0] == '\0')

// 	int i ;

// 	i = 0;
// 	while (line[i] && line[i] == ' ')
// 		i++;
// 	return (!ft_isdigit(line[i]));
// }



// int ft_arr_isnumber(char **new)
// {
// 	int i;

// 	i = 0;
// 	while(new[i])
// 	{
// 		if(!ft_isnumber(new[i]))
// 			return(0);//an element not a number
// 		i++;
// 	}
// 	return(1);// array of numbers
// }

/* 
void	clear(t_data *cubdata)
{
	int i;
	i = 0;
	while(cubdata->newline[i])
	{
		free(cubdata->newline[i]);
		i++;
	}
}
 */

// list of errors and referenced 





// R 78468 64588
// R  68554685456564564156431256896 5896
// ' SO ./pics/pillar.png'

			// if (cubdata->map[i][j] == ' ')
			// {
			// 	if ( j == 0 || j == len_j)



			// 	// 0   j - 1  j + 1 i - 1 j + 1  len

			// 	if (0 <= j + 1 && j + 1 <= len_j && 0 <= j - 1 && j - 1 <= len_j)
			// 	{
			// 		// printf("|%s|\n",cubdata->map[i]);
			// 		// printf("|%c|",cubdata->map[i][j - 1]);
			// 		// printf("%c|",cubdata->map[i - 1][j]);
			// 		// printf("%c|",cubdata->map[i - 1][j]);
			// 		// printf("%c|\n",cubdata->map[i + 1][j]);

			// 		if (!ft_surrounded(cubdata->map[i][j - 1], cubdata->map[i - 1][j], 
			// 	  cubdata->map[i][j + 1], cubdata->map[i + 1][j]))
			// 	  {
			// 		  ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
			// 	  }
			// 	  	//ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
			// 	}
			// }












			/*

// map valid **********************************


void first_last_line(char *first, char *last)
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
				ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
			i++;
		}
		else if (last[j])
		{
			if (last[j] != '1' && last[j] != ' ')
				ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
			j++;
		}
	}
}


void	ft_borders(char c1, char c2)
{
	//printf("ft_borders here |%c|%c|\n",c1,c2);
	if (c1 != '1' || c2 != '1')
		ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
}



int	ft_surrounded(char a, char b, char c , char d)
{
	printf("  |%c| \n",b);
	printf("|%c| ",a);
	printf("|%c|\n",c);
	printf("  |%c| \n\n",d);
	return((a == '1' || a == ' ') && (b == '1' || b == ' ') && (c == '1' || c == ' ') && (d == '1' || d == ' '));
}

int ft_each_map_line(char *str)
{
	//printf("\nhere|%s|\n",str);
	int i = -1;
	while(str[++i])
	{
		if ((str[i] < '0' ||  str[i] > '9') && str[i] != ' ' && str[i] != '2')
		{
			printf("ft_each_line: thats why o failed|%c|\n",str[i]);
			return (0);
		}//failed
	}
	return (1);
}


void	ft_mapvalid(t_data *cubdata)
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
	// if (cubdata->index < 3)
	// 	ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
	first_last_line(cubdata->map[0], cubdata->map[cubdata->index]);
	while(cubdata->map[++i]) 
	{
		
		str = ft_strtrim(cubdata->map[i], " ");
		if (!ft_each_map_line(cubdata->map[i])) // only numbers
			ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
		len = ft_strlen(str) - 1;
		ft_borders(str[0], str[len]);
		len_j =  ft_strlen(cubdata->map[i]) - 1;
		len_i = cubdata->index;
		j = 0;
		printf("|%s|i=%d|j=%d|\n",cubdata->map[i],len_i,len_j);
		while(cubdata->map[i][j]) // 3 lines
		{
			if (cubdata->map[i][j] == ' ')
			{
				if (0 <= j - 1  && j - 1 <= len_j)
					a = cubdata->map[i][j - 1];
				if (0 <= j + 1 && j + 1 <= len_j)
					c = cubdata->map[i][j + 1];
				if (0 <= i - 1 && i-1  <= len_i )
				{
					len_previous = ft_strlen(cubdata->map[i - 1]) - 1;
					if (len_previous < j)
						b = '1';
					else 
						b = cubdata->map[i - 1][j];
				}
				if (0 <= i + 1 && i + 1 <= len_i) // line exists
				{
					len_next= ft_strlen(cubdata->map[i+1]) - 1;
					if (len_next < j)
						d = '1';
					else
						d = cubdata->map[i + 1][j];
				}
				if (!ft_surrounded(a,b,c,d))
					ft_errors(micub_err[INVALID_MAP], micub_err[MAP]);
			}
			j++;
		}
	}
}
*/