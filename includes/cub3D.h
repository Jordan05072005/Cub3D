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
	double	orientation;
	size_t	size_bloc[2];
	int			co[2];
	int			old_co[2];
}					t_map_data;


typedef struct s_mini_map{
	void	*win;
	size_t	l;
	size_t	h;
}					t_mini_map;

typedef struct data{
	void *mlx;
	void *win;
	size_t l;
	size_t h;
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
int	move(int keycode, void *param);

//projection.c
void draw_projection(t_data *d, int color);



#endif
