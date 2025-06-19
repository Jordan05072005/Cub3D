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

int	collision_wall(int x, int y, t_map_data *m, t_data *d)
{
	int	x_base;
	int	y_base;
	int	xp;
	int	yp;

	xp = 0;
	yp = 0;
	x_base = x / m->size_bloc[0];
	y_base = y / m->size_bloc[1];
	if (x % m->size_bloc[0] > 0.5)
		xp = 1;
	if (y % m->size_bloc[1] > 0.5) // faire le carré
		yp = 1;
	// if (x_base < 0 || y_base < 0
	// 	|| y_base >= d->h
	// 	|| x_base >= d->w)
	// 		return (1);
	if ((m->maps[y_base][x_base] == '1' && )
		|| x_base < 0 || y_base < 0)
		return (1);
	return (0);
}

void	draw_wall(t_data *d, int xy[2], double angle, double fov, int col)
{
	double	di;
	double	h;
	int	y;

	di = sqrt((pow(xy[0] - d->mdata->co[0], 2) + pow(xy[1] - d->mdata->co[1], 2)));
	di *= cos(angle - d->mdata->orientation);
	if (di < 0.0001)
		di = 0.0001;
	h = (d->mdata->size_bloc[1] / di) * ((d->h / 2) / tan(fov));
	y = (d->h / 2) - h/2 - 1;
	while (++y < (d->h / 2) + h/2)
		mlx_pixel_put(d->mlx, d->win, col, y, 0xFF0000);
}

void draw_projection(t_data *d, int color)
{
	int			h;
	int			xy[2];
	int			col;
	double	angle;
	double	fov;
	double	ratio;

	fov = M_PI / 6;
	col = -1;
	while (++col < d->w)
	{
		ratio = (double)col / d->w;
		angle = d->mdata->orientation - fov + (2 * fov * ratio);
		h = 1;
		xy[0] = d->mdata->co[0];
		xy[1] = d->mdata->co[1];
		while (!collision_wall(xy[0], xy[1], d->mdata, d))
		{
			xy[0] = d->mdata->co[0] + cos(angle) * h;
			xy[1] = d->mdata->co[1] + sin(angle) * h;
			h++;
			mlx_pixel_put(d->mlx, d->mini->win, xy[0], xy[1] , color);
		}
		draw_wall(d, xy, angle, fov, col);
	}
}
