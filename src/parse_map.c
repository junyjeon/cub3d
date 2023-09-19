/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 06:03:27 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/19 19:58:06 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_player(t_map *map, int x, int y)
{
	double	angle;

	angle = 0.0;
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
	else
		angle = -PI_2;
	map->player.dirx = cos(angle);
	map->player.diry = sin(angle);
	map->player.planex = 0.66 * cos(angle - PI_2);
	map->player.planey = 0.66 * sin(angle - PI_2);
}

static int	**create_visited(t_map *map)
{
	int	**visited;
	int	i;

	visited = (int **)malloc(sizeof(int *) * map->row);
	if (!visited)
		err(map, "Malloc Fail visited");
	map->row_len = (int *)malloc(sizeof(int) * map->row);
	if (!map->row_len)
		err(map, "Malloc Fail row_len");
	i = -1;
	while (++i < map->row)
	{
		map->row_len[i] = ft_strlen(map->map[i]);
		visited[i] = (int *)malloc(sizeof(int) * map->row_len[i]);
		if (!visited[i])
		{
			while (i--)
				free(visited[i]);
			free(visited);
			err(map, "Malloc Fail");
		}
		memset(visited[i], 0, sizeof(int) * map->row_len[i]);
	}
	return (visited);
}

static void	parse_map_line(t_map *map)
{
	int	x;
	int	y;
	int	max_col;
	int	len;

	max_col = 0;
	x = -1;
	while (map->map[++x])
	{
		len = (int)ft_strlen(map->map[x]);
		if (len > max_col)
			max_col = len;
		y = -1;
		while (map->map[x][++y])
		{
			if (map->map[x][y] == 'N' || map->map[x][y] == 'S'\
			|| map->map[x][y] == 'E' || map->map[x][y] == 'W')
				init_player(map, x, y);
		}
	}
	if (!map->player.start_sight)
		err(map, "Invalid Player Data");
	map->row = x;
	map->col = max_col;
}

void	parse_map(t_map *map)
{
	map->map = ft_split(map->tmp_map, '\n');
	if (map->map == NULL)
		err(map, "Map Allocation Fail");
	free(map->tmp_map);
	map->tmp_map = NULL;
	parse_map_line(map);
	map->visited = create_visited(map);
	check_cover_wall(map);
}
