/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 03:43:21 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/04 05:53:48 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int ft_put_error(int fd, char *s)
{
    write(fd, s, ft_strlen(s));
    write(fd, "\n", 1);
    exit(1);
}

void	free_split(char **split)
{
	int i;

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

void	exit_error(t_map *map, char *s)
{
	ft_putendl_fd("ERROR", 2);
	if (s)
		ft_putendl_fd(s, 2);
	free_all(map);
	exit(1);
}
