/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:46:22 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/20 11:46:22 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x > 800 || y > 600 || x < 0 || y < 0)
	{
			return ;
	}
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	clear_frame(t_img *i, t_data *d)
{
	ft_memset(i->addr, 0, d->h * i->line_len); 
}

void	apply_frame(t_data *d, t_img *i)
{
	mlx_put_image_to_window(d->mlx, d->win, i->img_ptr, 0, 0);
	d->i = (d->i + 1) % 2;
	clear_frame(&d->img[d->i], d);
}
