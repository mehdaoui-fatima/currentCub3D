/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmehdaou <fmehdaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 11:30:10 by fmehdaou          #+#    #+#             */
/*   Updated: 2020/12/02 14:45:00 by fmehdaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/cub3d.h"

void	draw_wall(t_cub3d *cub)
{
	cub->x = 0;
	while (cub->x < cub->res.rx)
	{
		draw_wall_cx(cub);
		draw_wall_delta(cub);
		draw_wall_side(cub);
		cub->hit = 0;
		draw_wall_dda(cub);
		draw_wall_perp(cub);
		draw_wall_h_w(cub);
		drawline(cub->x, cub->drawstart, cub->drawend, cub);
		cub->zbuffer[(int)(cub->x)] = cub->perpwalldist;
		cub->x++;
	}
	draw_sprites(cub);
}
