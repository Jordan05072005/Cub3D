/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:36:15 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/16 15:36:15 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	max_line(char **maps)
{
	int max;
	int	i;

	max = 0;
	i = -1;
	while (maps[++i])
	{
		if (ft_strlen(maps[i]) > max)
			max = ft_strlen(maps[i]);
	}
	return (max);
}