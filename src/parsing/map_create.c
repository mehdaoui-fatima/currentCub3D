/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 14:05:09 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/01 16:54:20 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	ft_new_map(t_cub3d *cub)
{
	int		i;
	int		len;
	char	*s;

	i = -1;
	cub->maps.new_map = (char**)malloc(sizeof(char*) * (cub->maps.index + 2));
	cub->maps.new_map[cub->maps.index + 1] = NULL;
	while (cub->maps.map[++i])
	{
		len = ft_strlen(cub->maps.map[i]);
		s = (char*)malloc(sizeof(char) * (cub->maps.max_len - len + 1));
		s[cub->maps.max_len - len] = '\0';
		ft_memset(s, 32, cub->maps.max_len - len);
		cub->maps.new_map[i] = ft_strjoin(cub->maps.map[i], s);
		free(s);
	}
	ft_free(cub->maps.map);
}

void	sprites_pos(int *k, int i, int j, t_cub3d *cub)
{
	cub->sprites[*k].x = i + 0.5;
	cub->sprites[*k].y = j + 0.5;
	(*k)++;
}

void	ft_create_worldmap(t_cub3d *cub)
{
	int i;
	int j;
	int k;
	int len;

	i = -1;
	k = 0;
	cub->maps.worldMap = (int**)malloc(sizeof(int*) * (cub->maps.index + 1));
	while (cub->maps.new_map[++i])
	{
		cub->maps.worldMap[i] = (int*)malloc(sizeof(int) * cub->maps.max_len);
		j = -1;
		while (cub->maps.new_map[i][++j])
		{
			if (cub->maps.new_map[i][j] == '2')
				sprites_pos(&k, i, j, cub);
			if (cub->maps.new_map[i][j] == ' ')
				cub->maps.worldMap[i][j] = 1;
			else if (ft_isalpha((int)cub->maps.new_map[i][j]))
				cub->maps.worldMap[i][j] = 0;
			else
				cub->maps.worldMap[i][j] = cub->maps.new_map[i][j] - '0';
		}
	}
	ft_free(cub->maps.new_map);
}
