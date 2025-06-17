/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguaglio <guaglio.jordan@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 11:49:25 by jguaglio          #+#    #+#             */
/*   Updated: 2025/06/16 11:49:25 by jguaglio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void delstrr(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		free(str[i]);
	}
	free(str);
}

void ft_del(char **str)
{
	if (*str)
	{
		free(*str);
	}
	*str = NULL;
}

char	*ft_replace(char *str, char *replace)
{
	ft_del(&str);
	str = replace;
	return (str);
}
