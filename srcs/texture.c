/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabatail <pabatail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 15:17:00 by pabatail          #+#    #+#             */
/*   Updated: 2025/07/21 15:17:02 by pabatail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	load_texture(t_data *d, char *path, int index)
{
	t_texture *tex = &d->textures[index];

	tex->img_ptr = mlx_xpm_file_to_image(d->mlx, path, &tex->width, &tex->height);
	if (!tex->img_ptr)
		error_mess("Texture not found");
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->addr)
		error_mess("Failed to get texture data address");
}

unsigned int	get_texture_pixel(t_texture *tex, int x, int y)
{
	char *pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + y * tex->line_len + x * (tex->bpp / 8);
	return (*(unsigned int *)pixel);
}
