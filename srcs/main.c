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

int	k1(int keycode, void *p)
{
		t_data *d;

	d = (t_data *)p;
	d->keycode  = keycode;
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