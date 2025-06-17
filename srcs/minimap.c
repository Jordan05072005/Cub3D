/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:49:20 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/16 11:49:20 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	draw_rect(size_t size[2], int yb, int xb, t_data *d)
{
	int x;
	int	y;

	y = size[1] * yb;
	while (++y < (size[1] * (yb + 1)))
	{
		x = size[0] * xb;
		while(++x < (size[0] * (1 + xb)))
		{
			mlx_pixel_put(d->mlx, d->mini->win, x, y, 0xFF0000); // 0xFF0000 = rouge
		}
	}
}

void	draw_circle(void *mlx, void *win, int x0, int y0, int r, int color)
{
	int	x;
	int	y;

	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			if (x * x + y * y <= r * r)
				mlx_pixel_put(mlx, win, x0 + x, y0 + y, color);
			x++;
		}
		y++;
	}
}

void	draw_minmaps(t_map_data *m, t_data *d)
{
	int	x;
	int	y;

	y = -1;
	while (m->maps[++y])
	{
		x = -1;
		while (m->maps[y][++x])
		{
			if (m->maps[y][x] == '1')
				draw_rect(m->size_bloc, y, x ,d);
		}
	}
}

void	draw_player(t_map_data *m, t_data *d)
{
	draw_circle(d->mlx, d->mini->win, m->old_co[0]
		, m->old_co[1], 10,  0x000000);
	draw_circle(d->mlx, d->mini->win, m->co[0]
		, m->co[1], 10,  0xFFFF00);
}

//sortir de minimap
int	move(int keycode, void *p)
{
	t_data *d;

	d = (t_data *)p;
	draw_projection(d, 0x000000);
	if (keycode >= 65361 && keycode <= 65364)
	{
		d->mdata->old_co[0] = d->mdata->co[0];
		d->mdata->old_co[1] = d->mdata->co[1];
		mlx_clear_window(d->mlx, d->win);
	}
	if (keycode == 65362) //h
	{
		d->mdata->co[0] = d->mdata->co[0] + cos(d->mdata->orientation) * 10;
		d->mdata->co[1] = d->mdata->co[1] + sin(d->mdata->orientation) * 10;
	}
	else if (keycode == 65361) // g
		d->mdata->orientation -= (M_PI / 12);
	else if (keycode == 65363) // d
		d->mdata->orientation += (M_PI / 12);
	d->mdata->orientation = fmod(d->mdata->orientation, 2 * M_PI);
	draw_player(d->mdata, d);
	draw_projection(d, 0xFF0000);
}
