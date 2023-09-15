/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 03:43:21 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/15 19:48:49 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_put_err(char *s)
{
	write(2, "Error: ", 8);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit(1);
}

void	err(t_map *map, char *s)
{
	write(2, "Error: ", 8);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	free_all(map);
	exit(1);
}

int	exit_event(t_map *map)
{
	ft_putendl_fd("EXIT CUB3D", 0);
	// free_all(map);
	(void)map;
	exit(1);
}

void	free_split(char **split)
{
	int	i;

	if (split)
	{
		i = -1;
		while (split[++i])
		{
			free(split[i]);
			split[i] = NULL;
		}
		free(split);
		split = NULL;
	}
}

void	free_all(t_map *map)
{
	int	i;

	if (map->map)
	{
		i = -1;
		while (map->map[++i])
		{
			free(map->map[i]);
			map->map[i] = NULL;
		}
		free(map->map);
		map->map = NULL;
	}
	i = -1;
	while (++i < 4)
		if (map->tex[i].path)
			map->tex[i].path = NULL;
}
