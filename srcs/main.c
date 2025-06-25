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
	if (d->mdata->orientation == 'W')
		d->mdata->orientation = 0;
	else if (d->mdata->orientation == 'S')
		d->mdata->orientation = (3 * M_PI) / 2;
	else if (d->mdata->orientation == 'O')
		d->mdata->orientation = M_PI;
	else if (d->mdata->orientation == 'N')
		d->mdata->orientation = M_PI / 2;
	d->mdata->vel = 10;
	d->mdata->hitbox = 10;
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
	mlx_hook(data->mini->win, 2, 1L << 0, move, data);
	mlx_loop(data->mlx);
}