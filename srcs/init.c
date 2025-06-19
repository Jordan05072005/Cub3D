/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:49:28 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/16 11:49:28 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

t_map_data	*init_map_data()
{
	t_map_data *data;

	data = malloc(sizeof(t_map_data));
	data->tmaps = NULL;
	data->pathE = NULL;
	data->pathW = NULL;
	data->pathN = NULL;
	data->pathS = NULL;
	data->rgbC = 0;
	data->rgbF = 0;
	data->player = 0;
	return (data);
}

t_data *init_data(size_t l, size_t h)
{
	t_data *d;

	d = malloc(sizeof(t_data));
	d->mini = malloc(sizeof(t_mini_map));
	d->mlx = mlx_init();
	if (!d->mlx)
		return (NULL);
	d->w = l;
	d->h = h;
	d->mini->win = mlx_new_window(d->mlx, l, h, "Cub3D MiniMap");
	d->win = mlx_new_window(d->mlx, l, h, "Cub3D");
	d->mdata = init_map_data();
	return (d);
}

void init(int *lst, size_t s, int init)
{
	int	i;

	i = -1;
	while (++i < s)
		lst[i] = init;
}