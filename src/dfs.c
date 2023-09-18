/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 03:27:16 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/18 22:39:05 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	dfs(int x, int y, t_map *map)
{
	if (x < 0 || y < 0 || map->row <= x || map->col <= y)
		err(map, "invalid cover wall");
	if (map->map[x][y] == '1' || map->visited[x][y] == 1)
		return ;
	if (map->map[x][y] == '\n' || map->map[x][y] == ' '\
	|| map->map[x][y] == '\0')
		err(map, "invalid wall");
	map->visited[x][y] = 1;
	dfs(x + 1, y, map);
	dfs(x - 1, y, map);
	dfs(x, y + 1, map);
	dfs(x, y - 1, map);
}

void	check_cover_wall(t_map *map)
{
	int		i;
	int		x;
	int		y;
	int		len;

	x = -1;
	while (++x < map->row)
	{
		len = ft_strlen(map->map[x]);
		y = -1;
		while (++y < len)
			if (map->visited[x][y] == 0 && strchr("0NESW", map->map[x][y]) \
			&& map->map[x][y] != '\0')
				dfs(x, y, map);
	}
	i = -1;
	while (++i < map->row)
		free(map->visited[i]);
	free(map->visited);
}
