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

void	draw_wall(t_data *d, double xy[2], double angle, int col, int l, int color)
{
	double	di;
	double	h;
	int	y;

	di = l * cos(angle - d->mdata->orientation);
	if (di < 0.0001)
		di = 0.0001;
	h = (d->mdata->size_bloc[1] / di) * ((d->h / 4) / tan(d->mdata->fov));
	y = (d->h / 2) - h/2 ;
	while (++y < (d->h / 2) + h/2)
		my_mlx_pixel_put(&d->img[d->i], col, y, color);
}


void	draw_projection(t_data *d, int color)
{
	int		col;
	double	ratio;
	double	angle;
	double	dir_x, dir_y;
	double	ox = d->mdata->co[0];
	double	oy = d->mdata->co[1];

	double	fov = d->mdata->fov;
	double	camera_x;
	double	wall_x;
	int		line_height, draw_start, draw_end;
	double	dist;

	col = -1;
	while (++col < (int)d->w)
	{
		ratio = (double)col / d->w;
		angle = d->mdata->orientation - fov + 2 * fov * ratio;
		dir_x = cos(angle);
		dir_y = sin(angle);

		double ray_x = ox;
		double ray_y = oy;
		int step = 0;

		// Ray advance until wall
		while (!collision_wall(ray_x, ray_y, d->mdata, d))
		{
			ray_x = ox + dir_x * step;
			ray_y = oy + dir_y * step;
			step++;
		}

		dist = sqrt(pow(ray_x - ox, 2) + pow(ray_y - oy, 2));
		if (dist == 0)
			dist = 1;

		// Remove fish-eye
		dist *= cos(angle - d->mdata->orientation);

		line_height = (int)(d->h / dist);
		draw_start = -line_height / 2 + d->h / 2;
		draw_end = line_height / 2 + d->h / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= (int)d->h)
			draw_end = d->h - 1;

		// Determine wall direction
		int tex_index;
		int is_vertical = fabs(ray_x - floor(ray_x + 0.5)) < fabs(ray_y - floor(ray_y + 0.5));

		if (is_vertical && dir_x > 0)
			tex_index = 3; // West
		else if (is_vertical)
			tex_index = 2; // East
		else if (dir_y > 0)
			tex_index = 0; // North
		else
			tex_index = 1; // South

		// Wall X hit pos
		if (is_vertical)
			wall_x = ray_y;
		else
			wall_x = ray_x;
		wall_x -= floor(wall_x);
		int tex_x = (int)(wall_x * d->textures[tex_index].width);
		if ((is_vertical && dir_x > 0) || (!is_vertical && dir_y < 0))
			tex_x = d->textures[tex_index].width - tex_x - 1;

		// Draw column (using while loop)
		int y = draw_start;
		while (y < draw_end)
		{
			int d_pixel = y * 256 - d->h * 128 + line_height * 128;
			int tex_y = (d_pixel * d->textures[tex_index].height) / line_height / 256;
			unsigned int c = get_texture_pixel(&d->textures[tex_index], tex_x, tex_y);
			my_mlx_pixel_put(&d->img[d->i], col, y, c);
			y++;
		}
	}
}

