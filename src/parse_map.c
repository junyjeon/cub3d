/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 06:03:27 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/10 03:44:28 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	check_player_data(t_map *map, int row, int i)
{
	if (map->player.start_sight)
		err(map, "Invalid Player Data");
	else
		map->player.start_sight = map->map_malloc[row][i];
	map->player.posx = i;
	map->player.posy = row;
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
		visited[i] = (int *)malloc(sizeof(int) * col);
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
	int		x;
	int		y;
	int		**visited;

	map->map_malloc = ft_split(map->tmp_map_malloc, '\n');
	if (map->map_malloc == NULL)
		err(map, "Malloc Fail");
	x = -1;
	y = 0;
	while (map->map_malloc[++x] != NULL)
		parse_map_line(map, x, &y);
	if (map->player.start_sight == '\0')
		err(map, "Invalid Player Data");
	map->row = x;
	map->col = y;
	visited = create_visited(map, map->row, map->col);
	check_cover_wall(map, visited);
	// Todo.나중에 잘 프리하세용
	//free_split((char**)visited);
	// free_split(map->map_malloc);
	free(map->tmp_map_malloc);
	map->tmp_map_malloc = NULL;
}
