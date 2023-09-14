/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 06:03:27 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/14 17:34:25 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_player(t_map *map, int x, int y)
{
	double	angle;

	if (map->player.start_sight)
		err(map, "Invalid Player Data");
	else
		map->player.start_sight = map->map[x][y];
	map->player.posx = (double)x + 0.5;
	map->player.posy = (double)y + 0.5;
	if (map->map[x][y] == 'N')
		angle = PI;
	else if (map->map[x][y] == 'E')
		angle = PI_2;
	else if (map->map[x][y] == 'S')
		angle = 0;
	else if (map->map[x][y] == 'W')
		angle = -PI_2;
	map->player.dirx = -1.0;
	map->player.diry = 0.0;
	map->player.planex = 0.66;
	map->player.planex = 0.66;
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
		visited[i] = (int *)malloc(sizeof(int) * ft_strlen(map->map[i]));
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
	while (map->map[++x])
	{
		len = (int)ft_strlen(map->map[x]);
		if (len > i)
			i = len;
		y = -1;
		while (map->map[x][++y])
		{
			if (map->map[x][y] == 'N' || map->map[x][y] == 'S'\
			|| map->map[x][y] == 'E' || map->map[x][y] == 'W')
			init_player(map, x, y);
		}
	}
	if (map->player.start_sight == 0)
		err(map, "Invalid Player Data");
	// printf("%c", map->player.start_sight);
	map->row = x;
	map->col = y;
	// printf("row: %d, col: %d\n", map->row, map->col);
}

void	parse_map(t_map *map)
{
	int		**visited;

	map->map = ft_split(map->tmp_map, '\n');
	if (map->map == NULL)
		err(map, "Map Allocation Fail");
	parse_map_line(map);
	visited = create_visited(map, map->row, map->col);
	check_cover_wall(map, visited);
	int i = -1;
	while (++i < map->row)
		free(visited[i]);
	free(visited);
	free(map->tmp_map);
	map->tmp_map = NULL;
}
