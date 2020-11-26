
#include "../../header/cub3d.h"



void	ft_errors(char *error, char *str)
{
	ft_putendl_fd("Error\n", 1);
	ft_putstr_fd(error, 1);
	ft_putstr_fd(str, 1);
	exit(0);
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

int ft_len(char **newline)
{

	int i = 0;

	if (!newline)
		return (0);
	while(newline[i])
		i++;
	return(i);
}


void ft_free(char **s)
{
	int i;

	i = -1;
	while(s[++i])
	{
		free(s[i]);
		s[i] = NULL;
	}
	free(s);
	s = NULL;
}

int	ft_spaces(t_cub3d *cub)
{
	cub->getl.spaces = 0;
	while(cub->getl.line[cub->getl.spaces] == ' ')
		cub->getl.spaces++;
	return(cub->getl.spaces);
}
