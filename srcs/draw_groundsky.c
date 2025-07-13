/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_other.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 21:40:45 by jguaglio          #+#    #+#             */
/*   Updated: 2025/07/13 21:40:45 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	get_pixel_color(t_img *img, int x, int y)
{
	char	*pixel;
	int		color;

	// Adresse du pixel (dépend de la ligne et de la colonne)
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));

	// Lire la couleur (on suppose 32 bits ici, type int)
	color = *(unsigned int *)pixel;
	return (color);
}

void	draw_groundsky(t_data *d)
{
	int	x;
	int	y;
	int	top;
	int	color_top;
	int	color_below;

	color_below = (d->mdata->rgbF[0] << 16) | (d->mdata->rgbF[1] << 8) | d->mdata->rgbF[2];
	color_top = (d->mdata->rgbC[0] << 16) | (d->mdata->rgbC[1] << 8) | d->mdata->rgbC[2];

	y = -1;
	top = 1;
	while (++y < d->h)
	{
		x = -1;
		while (++x < d->w)
		{
			if (get_pixel_color(&d->img[d->i], x, y) != 0xFF0000 && top)
				my_mlx_pixel_put(&d->img[d->i], x, y , color_top);
			else if (get_pixel_color(&d->img[d->i], x, y) != 0xFF0000 && !top)
				my_mlx_pixel_put(&d->img[d->i], x, y , color_below);
			else if (y > d->h/2)
				top = 0;
		}
	}
}