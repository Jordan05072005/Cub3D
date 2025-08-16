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

	if (m->maps[yp][xp] == '1' && (xp >= (d->mdata->co[0] / m->size_bloc[0]) + 2 || 
xp <= (d->mdata->co[0] / m->size_bloc[0]) - 2))
		return (2);
  if (ft_strslen(m->maps) <= yp || ft_strlen(m->maps[yp]) <= xp|| m->maps[yp][xp] == '1')
        return 1;


		// 		xp < 0 || yp < 0
		// || yp >= ft_strslen(m->maps)
		// || xp >= max_line(m->maps)
		// || 
	return (0);
}

void	draw_wall(t_data *d, double angle, int x, int l)
{
	double	di;
	double	h;
	int			y;
	double	step;
	double	t;

	t = d->tex->y;
	di = l * cos(angle - d->mdata->orientation);
	if (di < 0.0001)
		di = 0.0001;
	h = (d->mdata->size_bloc[1] / di) * ((d->h / 4) / tan(d->mdata->fov));
	y = (d->h / 2) - h/2 ;
	ft_putnbr_fd(y, 1);
	ft_putchar_fd('\n', 1);
	step = d->tex->h / (((d->h / 2) + h/2) - y);
	while (++y < (d->h / 2) + h/2)
	{
		my_mlx_pixel_put(&d->img[d->i], d->tex, x, y);
		t += step;
		d->tex->y = t;
		if (d->tex->y >= d->tex->h)
			t = 0;
	}
}



void draw_projection(t_data *d, int color)
{
	int			h;
	double	xy[2];
	int			x;
	double	angle;
	double	ratio;

	x = -1;
	while (++x < d->w)
	{
		ratio = (double)x / d->w;
		angle = d->mdata->orientation
					- d->mdata->fov + (2 * d->mdata->fov * ratio);
		xy[0] = d->mdata->co[0];
		xy[1] = d->mdata->co[1];
		h = 1;
		while (!collision_wall(xy[0], xy[1], d->mdata, d))
		{
			xy[0] = d->mdata->co[0] + cos(angle) * h;
			xy[1] = d->mdata->co[1] + sin(angle) * h++;
			mlx_pixel_put(d->mlx, d->mini->win, xy[0], xy[1] , color);
		}
		if (1)
    	d->tex->x = (int)xy[1] % d->tex->w;
		else
   			d->tex->x = (int)xy[0] % d->tex->w;
		d->tex->y = 0;
		draw_wall(d, angle, x, h);
	}
}
