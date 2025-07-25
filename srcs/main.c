#include "../includes/cub3D.h"

int	render_frame(t_data *d)
{
	mlx_clear_window(d->mlx, d->win);
	draw_projection(d, 0x00FF00);
	draw_groundsky(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img[d->i].img_ptr, 0, 0);
	return (0);
}

int	init_textures(t_data *d)
{
	d->textures[0].img_ptr = mlx_xpm_file_to_image(d->mlx, "textures/wall_north.xpm", &d->textures[0].width, &d->textures[0].height);
	d->textures[1].img_ptr = mlx_xpm_file_to_image(d->mlx, "textures/wall_south.xpm", &d->textures[1].width, &d->textures[1].height);
	d->textures[2].img_ptr = mlx_xpm_file_to_image(d->mlx, "textures/wall_east.xpm", &d->textures[2].width, &d->textures[2].height);
	d->textures[3].img_ptr = mlx_xpm_file_to_image(d->mlx, "textures/wall_west.xpm", &d->textures[3].width, &d->textures[3].height);

	if (!d->textures[0].img_ptr || !d->textures[1].img_ptr || !d->textures[2].img_ptr || !d->textures[3].img_ptr)
		return (0);

	d->textures[0].addr = mlx_get_data_addr(d->textures[0].img_ptr, &d->textures[0].bpp, &d->textures[0].line_len, &d->textures[0].endian);
	d->textures[1].addr = mlx_get_data_addr(d->textures[1].img_ptr, &d->textures[1].bpp, &d->textures[1].line_len, &d->textures[1].endian);
	d->textures[2].addr = mlx_get_data_addr(d->textures[2].img_ptr, &d->textures[2].bpp, &d->textures[2].line_len, &d->textures[2].endian);
	d->textures[3].addr = mlx_get_data_addr(d->textures[3].img_ptr, &d->textures[3].bpp, &d->textures[3].line_len, &d->textures[3].endian);

	return (1);
}

int key_press(int keycode, t_data *d)
{
	t_map_data *m;

	m = d->mdata;
	if (keycode == 65307)
	{
		mlx_destroy_window(d->mlx, d->win);
		exit(0);
	}
	move(keycode, d);
	render_frame(d);

	return (0);
}

int close_window(t_data *d)
{
	mlx_destroy_window(d->mlx, d->win);
	exit(0);
}

void	fill_info(t_data *d)
{
	d->mdata->size_bloc[0] = d->w / max_line(d->mdata->maps);
	d->mdata->size_bloc[1] = d->h / ft_strslen(d->mdata->maps);
	d->mdata->co[0] = d->mdata->player[0] * d->mdata->size_bloc[0];
	d->mdata->co[1] = d->mdata->player[1] * d->mdata->size_bloc[1];
	d->mdata->old_co[0] = d->mdata->player[0] * d->mdata->size_bloc[0];
	d->mdata->old_co[1] = d->mdata->player[1] * d->mdata->size_bloc[1];
	d->mdata->fov = M_PI / 6;
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

int	main(int argc, char **argv)
{
	t_data	*d;
	t_map_data *m;
	
	if (argc != 2)
	{
		ft_putstr_fd("Usage: ./cub3D <map_file>\n", 2);
		return (1);
	}
	d = init_data(600, 800);
	m = init_map_data();
	if (!parser(argv[1], m))
	{
		ft_putstr_fd("Error parsing map\n", 2);
		return (1);
	}
	if (!init_textures(d))
	{
		ft_putstr_fd("Error initializing textures\n", 2);
		return (1);
	}
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, d->w, d->h, "Cub3D");
	mlx_loop_hook(d->mlx, render_frame, d);

	mlx_key_hook(d->win, key_press, d);
	mlx_hook(d->win, 17, 0, close_window, d);
	mlx_loop(d->mlx);
	return (0);
}
