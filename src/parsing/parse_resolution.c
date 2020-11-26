#include "../../header/cub3d.h"

void	resolution(t_cub3d *cub, char *micub_err[])
{
	cub->getl.newline = ft_split(cub->getl.line, ' ');
	if (ft_strcmp(cub->getl.newline[0], "R") == 0)
	{
		if (cub->getl.spaces > 0)
			ft_errors(micub_err[NOSPACESNEEDED], micub_err[RESOLUTION]);
		cub->getl.res = ft_len(cub->getl.newline);
		if (cub->getl.res != 3)
			ft_errors(micub_err[NUM_ARG], micub_err[RESOLUTION]);
		else if(cub->res.rx != -1)
			ft_errors(micub_err[DUP_LINE], micub_err[RESOLUTION]);
		else if (!(ft_isnumber(cub->getl.newline[1]) 
				&& ft_isnumber(cub->getl.newline[2])))
		ft_errors(micub_err[WRONG_DATA], micub_err[RESOLUTION]);
		else 
		{
			if (cub->getl.newline[1][0] == '-' || cub->getl.newline[2][0] == '-')
				ft_errors(micub_err[NON_NEGATIVE], micub_err[RESOLUTION]);
			cub->res.rx = ft_atoi(cub->getl.newline[1]);
			cub->res.ry = ft_atoi(cub->getl.newline[2]);
			cub->res.rx = (cub->res.rx > MAX_WIDTH || cub->res.rx <= 0) ? MAX_WIDTH : cub->res.rx;
			cub->res.ry = (cub->res.ry > MAX_HEIGHT || cub->res.ry <= 0) ? MAX_HEIGHT : cub->res.ry;
		}
	}
	else
		ft_errors(micub_err[INVALID_LINE], micub_err[RESOLUTION]);
	ft_free(cub->getl.newline);
}



