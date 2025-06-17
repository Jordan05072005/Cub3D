/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:49:35 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/16 11:49:35 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void fill_texture(char *id, char *other, t_map_data *data)
{
	if (!ft_strncmp(id, "NO", 3))
		data->pathN = other;
	else if (!ft_strncmp(id, "SO", 3))
		data->pathS = other;
	else if (!ft_strncmp(id, "WE", 3))
		data->pathW = other;
	else if (!ft_strncmp(id, "EA", 3))
		data->pathE = other;
}

void fill_rgb(char *id, char *other, t_map_data *data)
{
	char **number;

	number = ft_split(other, ',');
	if (id[0] == 'F')
	{
		data->rgbF = malloc(sizeof(int) * 3);
		data->rgbF[0] = ft_atoi(number[0]);
		data->rgbF[1] = ft_atoi(number[1]);
		data->rgbF[2] = ft_atoi(number[2]);
	}
	else if (id[0] == 'C')
	{
		data->rgbC = malloc(sizeof(int) * 3);
		data->rgbC[0] = ft_atoi(number[0]);
		data->rgbC[1] = ft_atoi(number[1]);
		data->rgbC[2] = ft_atoi(number[2]);
	}
	delstrr(number);
}

int	mapvalid(char c)
{
	if (c == '1' || c == '0' || c == 32)
		return (0);
	if (c == 'S' || c == 'N' )
		return (0);
	if (c == 'O' || c == 'E')
		return (0);
	return (1);
}

int	find_player(t_map_data *m)
{
	int	i;
	int	j;

	i = -1;
	while (m->maps[++i])
	{
		j = -1;
		while (m->maps[i][++j])
		{
			if (m->maps[i][j] == 'W' || m->maps[i][j] == 'E'
				|| m->maps[i][j] == 'S' || m->maps[i][j] == 'N')
			{
				m->player = malloc(sizeof(int) * 2);
				if (!m->player)
					return (1);
				m->player[0] = j;
				m->player[1] = i;
				m->orientation = m->maps[i][j];
			}
		}
	}
	return (0);
}

int parser(char *path, t_map_data *data)
{
	int fd;
	char	*line;
	char	*temp;
	char	**temp2;
	const char buf[1000];

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	line = get_next_line(fd);
	while (line)
	{
		temp = ft_strtrim(line, " ");
		if (ft_isdigit(temp[0]))
			data->tmaps = ft_strjoinf(data->tmaps, ft_strtrim(line, "\n"));
		else
		{
			temp2 = ft_split(temp, ' ');
			if (temp2[0] && ft_strlen(temp2[0]) == 2)
				fill_texture(temp2[0], temp2[1], data);
			else if (temp2[0] && ft_strlen(temp2[0]) == 1)
				fill_rgb(temp2[0], temp2[1], data);
		}
		ft_del(&temp);
		line = ft_replace(line, get_next_line(fd));
	}
	data->maps = ft_split(data->tmaps, '\r');
	return (find_player(data));
}