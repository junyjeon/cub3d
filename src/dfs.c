/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:38:25 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/07 19:07:58 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void dfs(int x, int y, t_map *map, int **visited)
{
	// indexing
	if (x < 0 || y < 0 || map->row <=  y || map->col <= x)
		err(map, "invalid wall1");
	// logical possible move ...
	if (map->map_malloc[y][x] == '1' || visited[y][x] == 1)
        return ;
	if (map->map_malloc[y][x] == '\n' || map->map_malloc[y][x] == ' '\
	|| map->map_malloc[y][x] == '\0')
		err(map, "invalid wall2");
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