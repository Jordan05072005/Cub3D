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

  if (m->maps[yp][xp] == '1')
        return 1;

		// 		xp < 0 || yp < 0
		// || yp >= ft_strslen(m->maps)
		// || xp >= max_line(m->maps)
		// || 

	return (0);
}

void	draw_wall(t_data *d, int xy[2], double angle, double fov, int col)
{
	double	di;
	double	h;
	int	y;

	int	i = -1;

	di = sqrt((pow(xy[0] - d->mdata->co[0], 2) + pow(xy[1] - d->mdata->co[1], 2)));
	di *= cos(angle - d->mdata->orientation);
	if (di < 0.0001)
		di = 0.0001;
	h = (d->mdata->size_bloc[1] / di) * ((d->h / 4) / tan(fov));
	y = (d->h / 2) - h/2 ;
	while (++y < (d->h / 2) + h/2)
		my_mlx_pixel_put(&d->img[d->i], col, y, 0xFF0000);
}


void draw_projection(t_data *d, int color)
{
	int			h;
	int			xy[2]; // double ??
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
