/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:49:31 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/16 11:49:31 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

#include <stdio.h>

void	fill_info(t_data *d)
{
	d->mdata->size_bloc[0] = d->w / max_line(d->mdata->maps);
	d->mdata->size_bloc[1] = d->h / ft_strslen(d->mdata->maps);
	d->mdata->co[0] = d->mdata->player[0] * d->mdata->size_bloc[0];
	d->mdata->co[1] = d->mdata->player[1] * d->mdata->size_bloc[1];
	d->mdata->old_co[0] = d->mdata->player[0] * d->mdata->size_bloc[0];
	d->mdata->old_co[1] = d->mdata->player[1] * d->mdata->size_bloc[1];
	d->keycode = 0;

	d->tex = malloc(sizeof(t_tex));
	d->tex->texture = mlx_xpm_file_to_image(d->mlx, "texture.xpm", &d->tex->w, &d->tex->h);
if (!d->tex->texture)
    exit(write(2, "Erreur XPM\n", 11));
// 2. Récupérer les données de la texture
	d->tex->data = mlx_get_data_addr(d->tex->texture, &d->tex->bpp, &d->tex->size_line, &d->tex->endian);


	d->mdata->fov = M_PI / 6;
	if (d->mdata->orientation == 'W')
		d->mdata->orientation = 0;
	else if (d->mdata->orientation == 'S')
		d->mdata->orientation = (3 * M_PI) / 2;
	else if (d->mdata->orientation == 'O')
		d->mdata->orientation = M_PI;
	else if (d->mdata->orientation == 'N')
		d->mdata->orientation = M_PI / 2;
	d->mdata->vel = 3;
	d->mdata->hitbox = 10;
}

int	k1(int keycode, void *p)
{
		t_data *d;

	d = (t_data *)p;
	d->keycode  =keycode;
	return( 2 );
}

int	k2(int keycode, void *p)
{
		t_data *d;

	d = (t_data *)p;
	d->keycode = 0;
	return (1);
}

int main(int argc, char **argv)
{
	t_data *data;

	if (argc != 2)
		return (error_mess("Number of arguments"), 1);
	data = init_data(800, 600);
	if (!data)
		return (1);
	if (parser(argv[1], data->mdata))
		return (error_mess("I can't open file"), 1);
	if (error_handling(data->mdata))
		return (error_mess("Maps incorrect"), 1);
	fill_info(data);
	draw_minmaps(data->mdata, data);

	// mlx_hook(data->win, 2, 1L << 0, move, data);
	mlx_hook(data->win, 2, 1L << 0, k1, data);
	mlx_hook(data->win, 3, 1L << 1, k2, data);
	mlx_loop_hook(data->mlx, move, data);
	mlx_loop(data->mlx);
}