/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 06:03:27 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/04 06:08:09 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void dfs(int x, int y, t_map *map, int **visited) {
    if (x < 0 || y < 0 || x >= map->row || y >= map->col || map->map_malloc[y][x] == '1')
        return;
    if (visited[y][x])
        return;
    visited[y][x] = 1;
    dfs(x + 1, y, map, visited);
    dfs(x - 1, y, map, visited);
    dfs(x, y + 1, map, visited);
    dfs(x, y - 1, map, visited);
}

static void	check_player_data(t_map *map, int row, int i)
{
	if (map->player.starting_sight)
		exit_error(map, "Invalid Player Data");
	else
		map->player.starting_sight = map->map_malloc[row][i];
	map->player.px = i;
	map->player.py = row;
}

static int **create_visited(t_map *map, int row, int col)
{
	int **visited;
	int i;

	visited = (int **)malloc(sizeof(int *) * row);
	if (!visited)
		exit_error(map, "Memory allocation failed");
	for (i = 0; i < row; i++)
	{
		visited[i] = (int *)malloc(sizeof(int) * col);
		if (!visited[i])
		{
			while (i--)
				free(visited[i]);
			free(visited);
			exit_error(map, "Memory allocation failed");
		}
		memset(visited[i], 0, sizeof(int) * col);
	}
	return visited;
}

static void	parse_map_line(t_map *map, int row, int *col)
{
	int		i;
	int		len;

	len = (int)ft_strlen(map->map_malloc[row]);
	if (len > *col)
		*col = len;
	i = -1;
	while (map->map_malloc[row][++i])
	{
		if (map->map_malloc[row][i] == 'N' || map->map_malloc[row][i] == 'S'\
		 || map->map_malloc[row][i] == 'E' || map->map_malloc[row][i] == 'W')
			check_player_data(map, row, i);
	}
}

void	parse_map(t_map *map)
{
	int		row;
	int		col;
	int		**visited;

	map->map_malloc = ft_split(map->tmp_map_malloc, '\n');
	if (map->map_malloc == NULL)
		exit_error(map, NULL);
	row = -1;
	col = 0;
	while (map->map_malloc[++row] != NULL)
	{
		parse_map_line(map, row, &col);
	}
	if (map->player.starting_sight == '\0')
		exit_error(map, "Invalid Player Data");
	map->row = row;
	map->col = col;

	visited = create_visited(map, map->row, map->col);
	dfs(map->player.px, map->player.py, map, visited);

	for (int i = 0; i < map->row; i++)
		free(visited[i]);
	free(visited);

	free_split(map->map_malloc);
	free(map->tmp_map_malloc);
	map->tmp_map_malloc = NULL;
}
