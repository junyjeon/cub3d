/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 06:03:27 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/10 20:28:41 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	check_player_data(t_map *map, int x, int y)
{
	if (map->player.start_sight)
		err(map, "Invalid Player Data");
	else
		map->player.start_sight = map->map_malloc[x][y];
	map->player.posx = x;
	map->player.posy = y;
}

static int	**create_visited(t_map *map, int row, int col)
{
	int	**visited;
	int	i;

	visited = (int **)malloc(sizeof(int *) * row);
	if (!visited)
		err(map, "Malloc Fail");
	i = -1;
	while (++i < row)
	{
		visited[i] = (int *)malloc(sizeof(int) * ft_strlen(map->map_malloc[i]));
		if (!visited[i])
		{
			while (i--)
				free(visited[i]);
			free(visited);
			err(map, "Malloc Fail");
		}
		memset(visited[i], 0, sizeof(int) * col);
	}
	return (visited);
}

static void	parse_map_line(t_map *map)
{
	int	x;
	int	y;
	int	i;
	int	len;

	i = 0;
	x = -1;
	while (map->map_malloc[++x])
	{
		len = (int)ft_strlen(map->map_malloc[x]);
		if (len > i)
			i = len;
		y = -1;
		while (map->map_malloc[x][++y])
		{
			if (map->map_malloc[x][y] == 'N' || map->map_malloc[x][y] == 'S'\
			|| map->map_malloc[x][y] == 'E' || map->map_malloc[x][y] == 'W')
			check_player_data(map, x, y);
		}
	}
	if (map->player.start_sight == 0)
		err(map, "Invalid Player Data");
	map->row = x;
	map->col = y;
}

void	parse_map(t_map *map)
{
	int		**visited;

	map->map_malloc = ft_split(map->tmp_map_malloc, '\n');
	if (map->map_malloc == NULL)
		err(map, "Map Allocation Fail");
	parse_map_line(map);
	visited = create_visited(map, map->row, map->col);
	check_cover_wall(map, visited);
	int i = -1;
	while (++i < map->row)
		free(visited[i]);
	free(visited);
	free(map->tmp_map_malloc);
	map->tmp_map_malloc = NULL;
}
