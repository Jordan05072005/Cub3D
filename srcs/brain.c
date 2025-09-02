/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 16:05:15 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/18 16:05:15 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"


#include <sys/time.h>
double	get_time(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

double	adjust_x(t_map_data *m, int hitbox)
{
	static double	last_time = 0;
	double	now = get_time();
	double	delta_time = now - last_time;
	last_time = now;
	// if (hitbox)
	// 	return (m->co[0]
	// 		+ cos(m->orientation) * (m->vel + m->hitbox));
	return (m->co[0]
			+ cos(m->orientation) * (m->vel));
}

double adjust_y(t_map_data *m, int hitbox)
{
	static double	last_time = 0;
	double	now = get_time();
	double	delta_time = now - last_time;

	// if (hitbox)
	// 	return (m->co[1] 
	// 		+ sin(m->orientation) * (m->vel + m->hitbox));
	return (m->co[1] 
		+ sin(m->orientation) * (m->vel));
}


int	move(void *p)
{
	t_data *d;
	t_map_data *m;

	d = (t_data *)p;
	m = d->mdata;
	if (d->keycode >= 65361 && d->keycode <= 65363)
	{
		//draw_projection(d, 0x000000);
		if (d->keycode == 65362
			&& collision_player(adjust_x(m, 0), adjust_y(m, 0), m, d))
		{
			m->old_co[0] = m->co[0];
			m->old_co[1] = m->co[1];
			m->co[0] = adjust_x(m, 0);
			m->co[1] = adjust_y(m, 0);
		}
		else if (d->keycode == 65361 ) // g
			m->orientation -= (M_PI / 12 / 6);
		else if (d->keycode == 65363) // d
			m->orientation += (M_PI / 12 / 6);
		m->orientation = fmod(m->orientation, 2 * M_PI);
		draw_player(m, d, m->co, 0xFFFF00);
		draw_projection(d, 0xFF0000);
		draw_groundsky(d);
		apply_frame(d, &d->img[d->i]);
	}
}