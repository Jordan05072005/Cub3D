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

void	draw_wall(t_data *d, double angle, int x, double l)
{
	double	di;
	double	h;
	double	y;
	double	step;
	double	t;

	t = d->tex->y;
	di = l * cos(angle - d->mdata->orientation);
	if (di < 0.0001)
		di = 0.0001;
	h = (d->mdata->size_bloc[1] / di) * ((d->h / 4) / tan(d->mdata->fov));
	y = (int)ceil((d->h / 2) - h/2);
	step = d->tex->h / h;
	int ty;
	while (y < (d->h / 2) + h/2 && y < d->h)
	{
		my_mlx_pixel_put(&d->img[d->i], d->tex, x, y);
		t += step;
		d->tex->y = t;
		if (d->tex->y >= d->tex->h)
			t = 0;
		y++;
	}
}


void draw_projection(t_data *d, int color)
{
	t_casting c;
	double	xy[2];
	int			x;

	x = -1;
	while (++x < d->w)
	{
		c.r = (double)x / d->w;
		c.angle = d->mdata->orientation
					- d->mdata->fov + (2 * d->mdata->fov * c.r);
		c.pas = 0;
		xy[0] = d->mdata->co[0] + cos(c.angle);
		xy[1] = d->mdata->co[1] + sin(c.angle);
		c.ray_step = 1;
		while (!collision_wall(xy[0], xy[1], d->mdata, d))
		{
			xy[0] = d->mdata->co[0] + cos(c.angle) * c.pas;
			xy[1] = d->mdata->co[1] + sin(c.angle) * c.pas;
			c.pas += c.ray_step;
		}
		c.pas -= (c.ray_step * 2);
		xy[0] = d->mdata->co[0] + cos(c.angle) * c.pas;
		xy[1] = d->mdata->co[1] + sin(c.angle) * c.pas;
		c.ray_step = 0.1;
		while (!collision_wall(xy[0], xy[1], d->mdata, d))
		{
			c.pas += c.ray_step;
			xy[0] = d->mdata->co[0] + cos(c.angle) * c.pas;
			xy[1] = d->mdata->co[1] + sin(c.angle) * c.pas;
			//mlx_pixel_put(d->mlx, d->mini->win, xy[0], xy[1] , 0xFF0000);
		}
		c.sz[0] = d->mdata->size_bloc[0];
		c.sz[1] = d->mdata->size_bloc[1];
		c.lc[0] = fmod(xy[0], d->mdata->size_bloc[0]);
		c.lc[1] = fmod(xy[1], d->mdata->size_bloc[1]);
		if (c.lc[0] < 0.0)
			c.lc[0] += c.sz[0];
		if (c.lc[1] < 0.0)
			c.lc[1] += c.sz[1];
		if (fabs(c.lc[0]) < c.ray_step || fabs(c.lc[0] - c.sz[0]) < c.ray_step)
			d->tex->x = (int)((c.lc[1] / c.sz[1]) * d->tex->w);
		else
			d->tex->x = (int)((c.lc[0] / c.sz[0]) * d->tex->w);
		d->tex->y = 0;
		draw_wall(d, c.angle, x, c.pas);
	}
}
