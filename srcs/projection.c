/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 09:15:03 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/17 09:15:03 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	collision_wall(int x, int y, t_map_data *m)
{
	int	x_base;
	int	y_base;

	x_base = x / m->size_bloc[0];
	y_base = y / m->size_bloc[1];
	if (m->maps[y_base][x_base] == '1' || x_base < 0 || y_base < 0)
		return (1);
	return (0);
}

void	draw_wall(t_data *d, int xp, int yp, int angle, int t)
{
	int	di;
	int	h;
	ft_putstr_fd("\n\n\n", 1);
	ft_putnbr_fd(t, 1);
	// for (int x = t ; x < (t + 8); x++){
		di = sqrt((pow(xp - d->mdata->co[0], 2) + pow(yp - d->mdata->co[1], 2)));
		di /= cos(angle - d->mdata->orientation);
		ft_putnbr_fd(di, 1);
		ft_putstr_fd("\n", 1);
		h = 600 / di;
		for (int y = 300 - h/2; y < 300 + h/2; y++)
			mlx_pixel_put(d->mlx, d->win, t, y, 0xFF0000);
	// }
}

void draw_projection(t_data *d, int color)
{
	int			i;
	int			x;
	int			y;
	int			t = 0;
	double	angle_lasers;
	double	fov;	

	fov = M_PI / 6;
	angle_lasers = d->mdata->orientation + fov;
	while (angle_lasers > (d->mdata->orientation - fov))
	{
		i = -1;
		x = d->mdata->co[0];
		y = d->mdata->co[1];
		while (!collision_wall(x, y, d->mdata))
		{
			x = d->mdata->co[0] + cos(angle_lasers) * ( i );
			y = d->mdata->co[1] + sin(angle_lasers) * ( i );
			i++;
			mlx_pixel_put(d->mlx, d->mini->win, x, y , color);
		}
		draw_wall(d, x, y, angle_lasers, t);
		t+=1;
		angle_lasers -=  (M_PI / 3) / 800;
	}
}
