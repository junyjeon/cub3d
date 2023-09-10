/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 03:27:16 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/10 20:03:27 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	dfs(int x, int y, t_map *map, int **visited)
{
	if (x < 0 || y < 0 || map->row <= y || map->col <= x)
		err(map, "invalid cover wall");
	if (map->map_malloc[y][x] == '1' || visited[y][x] == 1)
		return ;
	if (map->map_malloc[y][x] == '\n' || map->map_malloc[y][x] == ' '\
	|| map->map_malloc[y][x] == '\0')
		err(map, "invalid wall");
	visited[y][x] = 1;
	dfs(x + 1, y, map, visited);
	dfs(x - 1, y, map, visited);
	dfs(x, y + 1, map, visited);
	dfs(x, y - 1, map, visited);
	dfs(x + 1, y + 1, map, visited);
	dfs(x - 1, y + 1, map, visited);
	dfs(x + 1, y - 1, map, visited);
	dfs(x - 1, y - 1, map, visited);
}

void	check_cover_wall(t_map *map, int **visited)
{
	int		x;
	int		y;
	int		len;

	x = -1;
	while (++x < map->row)
	{
		len = ft_strlen(map->map_malloc[x]);
		y = -1;
		while (++y < len)
			if (visited[x][y] == 0 && strchr("0NESW", map->map_malloc[x][y]\
			&& map->map_malloc[x][y] != '\0'))
				dfs(x, y, map, visited);
	}
}
