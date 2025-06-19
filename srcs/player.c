/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:05:15 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/18 16:05:15 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	collision_maps(double x, double y, t_data *d)
{
	if (x >= d->w || x <= 0)
		return (1);
	if (y >= d->h || y <= 0)
		return (1);
	return (0);
}

int	collision_wall_now(t_data *d)
{
	if (d->mdata->maps[d->mdata->co[1] / d->mdata->size_bloc[1]]
		[d->mdata->co[0] / d->mdata->size_bloc[0]] == '1')
	{
		draw_player(d->mdata, d, d->mdata->old_co, 0x000000);
		return (1);
	}
	return (0);
}

int	move(int keycode, void *p)
{
	t_data *d;

	d = (t_data *)p;

	ft_putstr_fd("hello", 1);
	if (keycode >= 65361 && keycode <= 65363)
	{
		draw_projection(d, 0x000000);
		if (!collision_wall_now(d))
		{
			d->mdata->old_co[0] = d->mdata->co[0];
			d->mdata->old_co[1] = d->mdata->co[1];
		}
		mlx_clear_window(d->mlx, d->win);
		if (keycode == 65362 && !collision_maps(d->mdata->co[0]
			+ cos(d->mdata->orientation) * 10, d->mdata->co[1]
			+ sin(d->mdata->orientation) * 10, d))
		{
			d->mdata->co[0] = d->mdata->co[0] + cos(d->mdata->orientation) * 10;
			d->mdata->co[1] = d->mdata->co[1] + sin(d->mdata->orientation) * 10;
		}
		else if (keycode == 65361) // g
			d->mdata->orientation -= (M_PI / 12);
		else if (keycode == 65363) // d
			d->mdata->orientation += (M_PI / 12);
		d->mdata->orientation = fmod(d->mdata->orientation, 2 * M_PI);
		if (!collision_wall_now(d))
		{
			draw_player(d->mdata, d, d->mdata->co, 0xFFFF00);
		}
		draw_projection(d, 0xFF0000);

	}
}