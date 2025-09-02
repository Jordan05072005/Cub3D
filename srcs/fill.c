/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:16:12 by jguaglio          #+#    #+#             */
/*   Updated: 2025/08/30 16:16:12 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void	fill_info(t_data *d)
{
	d->mdata->size_bloc[0] = d->w / max_line(d->mdata->maps);
	d->mdata->size_bloc[1] = d->h / ft_strslen(d->mdata->maps);
	d->mdata->co[0] = d->mdata->player[0] * d->mdata->size_bloc[0];
	d->mdata->co[1] = d->mdata->player[1] * d->mdata->size_bloc[1];
	d->mdata->old_co[0] = d->mdata->player[0] * d->mdata->size_bloc[0];
	d->mdata->old_co[1] = d->mdata->player[1] * d->mdata->size_bloc[1];
	d->keycode = 0;

	d->tex[0].tex= mlx_xpm_file_to_image(d->mlx, "tex/texture.xpm", &d->tex[0].w, &d->tex[0].h);
if (!d->tex[0].tex)
    exit(write(2, "Erreur XPM\n", 11));
// 2. Récupérer les données de la texture
	d->tex[0].data = mlx_get_data_addr(d->tex[0].tex, &d->tex[0].bpp, &d->tex[0].size_line, &d->tex[0].endian);

	d->tex[1].tex= mlx_xpm_file_to_image(d->mlx, "tex/bookshelf.xpm", &d->tex[1].w, &d->tex[1].h);
if (!d->tex[1].tex)
    exit(write(2, "Erreur XPM\n", 11));
// 2. Récupérer les données de la texture
	d->tex[1].data = mlx_get_data_addr(d->tex[1].tex, &d->tex[1].bpp, &d->tex[1].size_line, &d->tex[1].endian);

		d->tex[2].tex= mlx_xpm_file_to_image(d->mlx, "tex/mossy_cobblestone1.xpm", &d->tex[2].w, &d->tex[2].h);
if (!d->tex[2].tex)
    exit(write(2, "Erreur XPM\n", 11));
// 2. Récupérer les données de la texture
	d->tex[2].data = mlx_get_data_addr(d->tex[2].tex, &d->tex[2].bpp, &d->tex[2].size_line, &d->tex[2].endian);

	d->tex[3].tex= mlx_xpm_file_to_image(d->mlx, "tex/mycelium_top.xpm", &d->tex[3].w, &d->tex[3].h);
if (!d->tex[3].tex)
    exit(write(2, "Erreur XPM\n", 11));
// 2. Récupérer les données de la texture
	d->tex[3].data = mlx_get_data_addr(d->tex[3].tex, &d->tex[3].bpp, &d->tex[3].size_line, &d->tex[3].endian);


	d->mdata->fov = M_PI / 6;
	if (d->mdata->orientation == 'W')
		d->mdata->orientation = 0;
	else if (d->mdata->orientation == 'S')
		d->mdata->orientation = (3 * M_PI) / 2;
	else if (d->mdata->orientation == 'O')
		d->mdata->orientation = M_PI;
	else if (d->mdata->orientation == 'N')
		d->mdata->orientation = M_PI / 2;
	d->mdata->vel = 0.5;
	d->mdata->hitbox = 10;
}