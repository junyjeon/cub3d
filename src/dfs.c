/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 20:38:25 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/03 20:59:44 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool isOutOfMap(int x, int y, t_map *map) {
    return x < 0 || x >= map->row || y < 0 || y >= strlen(map->map_malloc[x]);
}

bool dfs(t_map *map, int x, int y, bool **visited) {
    if (isOutOfMap(x, y, map)) {
        return true;
    }

    if (visited[x][y] || map->map_malloc[x][y] == '1') {
        return false;
    }

    visited[x][y] = true;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int newX = x + dx[i];
        int newY = y + dy[i];
        if (dfs(map, newX, newY, visited)) {
            return true;
        }
    }

    return false;
}

bool isMapClosed(t_map *map) {
    bool visited[map->map_malloc][map->map_malloc] = {false};

    for (int i = 0; i < map->row; i++) {
        for (int j = 0; j < strlen(map->map_malloc[i]); j++) {
            if (map->map_malloc[i][j] == '0' && !visited[i][j]) {
                if (dfs(map, i, j, visited)) {
                    return false;
                }
            }
        }
    }

    return true;
}