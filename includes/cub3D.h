#ifndef CUB3D_H
# define CUB3D_H

#include "../mlx/mlx.h"
#include <fcntl.h>
#include "../libft/libft.h"
#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

typedef struct s_map_data{
	char		*pathN;
	char		*pathS;
	char		*pathW;
	char		*pathE;
	int			*rgbF;
	int			*rgbC;
	char		*tmaps;
	char		**maps;
	int			*player;
	int			vel;
	int			hitbox;
	double	fov;
	double	orientation;
	size_t	size_bloc[2];
	int			co[2];
	int			old_co[2];
}					t_map_data;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;


typedef struct s_mini_map{
	void	*win;
	size_t	w;
	size_t	h;
}					t_mini_map;

typedef struct s_texture{
	void*	texture;
	char	*data;
	int		bpp;
	int		size_line;
	int		x;
	int		y;
	int		w;
	int		h;
	int		endian;
}				t_tex;

 typedef struct s_casting{
	double	angle;
	double	r;
	double	ray_step;
	double	pas;
	double	sz[2];
	double lc[2];

 }	t_casting;


typedef struct data{
	void *mlx;
	void *win;
	int	keycode;
	size_t w;
	size_t h;
	t_img *img;
	t_tex	*tex;
	int		i;
	t_mini_map *mini;
	t_map_data *mdata;
}				t_data;

void delstrr(char **str);
void ft_del(char **str);
char	*ft_replace(char *str, char *replace);

//parser.c
int	parser(char *path, t_map_data *data);
int	mapvalid(char c);


//error.c
void error_mess(char *mess);
int	error_handling(t_map_data *data);

//init.c
t_data *init_data(size_t h, size_t l);
t_map_data	*init_map_data();
void init(int *lst, size_t s, int init);

//utils.c
int	max_line(char **maps);

//minimap.c
void	draw_minmaps(t_map_data *m, t_data *d);
int	move(void *param);
void	draw_player(t_map_data *m, t_data *d, int co[2], int color);

//projection.c
void draw_projection(t_data *d, int color);

//collision.c
int	collision_wall(double x, double y, t_map_data *m, t_data *d);
int	collision_player(double x, double y, t_map_data *m, t_data *d);

//frame.c
void	my_mlx_pixel_put_c(t_img *img, int x, int y, int color);
void	my_mlx_pixel_put(t_img *img, t_tex *t, int x, int y);
void	apply_frame(t_data *d, t_img *i);


//draw_groundsky.c
void	draw_groundsky(t_data *d);




#endif
