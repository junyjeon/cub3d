/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pre.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 02:46:23 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/10 19:38:39 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	*parse_texture(t_map *map, char *path_line)
{
	int		fd;
	char	*path;

	path = path_line + 3;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		err(map, "Invalid .xpm File");
	close(fd);
	return (ft_strdup(path));
}

static int	parse_color(t_map *map, char *line)
{
	int		i;
	int		j;
	int		color;
	char	**rgb;

	rgb = ft_split(line + 2, ',');
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
		err(map, "Invalid Color");
	j = -1;
	while (rgb[++j])
	{
		i = -1;
		while (rgb[j][++i])
			if (!ft_isdigit(rgb[j][i]))
				err(map, "Invalid Color");
	}
	color = ft_atoi(rgb[0]) * 256 * 256 + ft_atoi(rgb[1]) * 256 + ft_atoi(rgb[2]);
	if (color < 0 || 0xFFFFFF < color)
		err(map, "Invalid Color");
	free_split(rgb);
	return (color);
}

static void	save_map(t_map *map, char *line, int validate)
{
	if (validate == NO)
		map->tex[NO].path = parse_texture(map, line);
	else if (validate == SO)
		map->tex[SO].path = parse_texture(map, line);
	else if (validate == WE)
		map->tex[WE].path = parse_texture(map, line);
	else if (validate == EA)
		map->tex[EA].path = parse_texture(map, line);
	else if (validate == FLOOR)
		map->floor_color = parse_color(map, line);
	else if (validate == CEIL)
		map->ceil_color = parse_color(map, line);
	else if (validate == MAP)
		map->tmp_map_malloc = join_all_lines(map->tmp_map_malloc, line);
	else if (validate == EMPTY_LINE)
		return ;
	else if (validate == ERROR)
		err(map, "Invalid Data");
	else
		err(map, "Unexpected validate value");
}

static int	validate_map_line(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (NO);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (SO);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (WE);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (EA);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (FLOOR);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (CEIL);
	if (ft_strchr("01NSWE ", line[0]) != NULL)
		return (MAP);
	if (line[0] == '\n')
		return (EMPTY_LINE);
	if (line[0] == '\0')
		return (END);
	return (ERROR);
}

void	process_lines(t_map *map, char **lines)
{
	int	i;

	i = -1;
	while (lines[++i])
	{
		save_map(map, lines[i], validate_map_line(lines[i]));
		free(lines[i]);
	}
}
