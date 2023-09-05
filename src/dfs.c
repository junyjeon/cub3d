/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:38:25 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/05 20:49:32 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void dfs(int x, int y, t_map *map, int **visited)
{
	if (x < 0 || y < 0 || x >= map->row || y >= map->col \
	|| map->map_malloc[y][x] == '1')
        return ();
    if (visited[y][x])
        return ();
    visited[y][x] = 1;
    dfs(x + 1, y, map, visited);
    dfs(x - 1, y, map, visited);
    dfs(x, y + 1, map, visited);
    dfs(x, y - 1, map, visited);
}