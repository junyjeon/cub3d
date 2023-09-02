/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 03:43:21 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/03 03:43:34 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

void	free_all(t_map *map)
{
	int	i;

	if (map->tmp_map_malloc)
		free(map->tmp_map_malloc);
	map->tmp_map_malloc = NULL;
	if (map->map_malloc)
	{
		i = -1;
		while (map->map_malloc[++i])
		{
			free(map->map_malloc[i]);
			map->map_malloc[i] = NULL;
		}
		free(map->map_malloc);
	}
	i = -1;
	while (++i < 4)
	{
		if (map->tex[i].tex_path_malloc)
		{
			free(map->tex[i].tex_path_malloc);
			map->tex[i].tex_path_malloc = NULL;
		}
	}
}

void	exit_error(t_map *map, char *message)
{
	ft_putendl_fd("ERROR", 2);
	if (message)
		ft_putendl_fd(message, 2);
	free_all(map);
	exit(1);
}
