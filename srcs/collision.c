/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 12:49:13 by jguaglio          #+#    #+#             */
/*   Updated: 2025/08/19 12:49:13 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	collision_player(double x, double y, t_map_data *m, t_data *d)
{
	int	xp[5];
	int	yp[5];
	int	h = m->hitbox;
	int	i;

	i = -1;

	xp[0] = (x - h) / m->size_bloc[0];
	yp[0] = y / m->size_bloc[1];
	xp[1] = x / m->size_bloc[0];
	yp[1] = (y - h) / m->size_bloc[1];
	xp[2] = (x + h) / m->size_bloc[0];
	yp[2] = y / m->size_bloc[1];
	xp[3] = x / m->size_bloc[0];
	yp[3] = (y + h) / m->size_bloc[1];
	xp[4] = x / m->size_bloc[0];
	yp[4] = y / m->size_bloc[1];


		// if (ft_strslen(m->maps) <= yp[3] || ft_strlen(m->maps[xp[1]]) <= xp[2])
		//   return 1;
	while (++i < 5)
	{
		ft_putnbr_fd(yp[i], 1);
		ft_putstr_fd("\n", 1);
		ft_putnbr_fd(xp[i], 1);
		ft_putstr_fd("\n", 1);


		if (m->maps[yp[i]][xp[i]] == '1')
			return (1);
	}
			ft_putstr_fd("\n", 1);
		ft_putstr_fd("\n", 1);
}

int	collision_wall(double x, double y, t_map_data *m, t_data *d)
{
	int	xp;
	int	yp;

	xp = x / m->size_bloc[0];
	yp = y / m->size_bloc[1];
	// ft_putnbr_fd(xp, 1);
	// ft_putchar_fd('\n', 1);
	// ft_putnbr_fd(yp, 1);
	// ft_putchar_fd('\n', 1);

	if (m->maps[yp][xp] == '1')
		return (2);
  if (ft_strslen(m->maps) <= yp || ft_strlen(m->maps[yp]) <= xp|| m->maps[yp][xp] == '1')
        return 1;


		// 		xp < 0 || yp < 0
		// || yp >= ft_strslen(m->maps)
		// || xp >= max_line(m->maps)
		// || 
	return (0);
}