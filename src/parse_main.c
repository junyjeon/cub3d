/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 02:46:23 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/20 03:34:15 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	check_color(char *line)
{
	char	**color;
	int		i;
	int		j;

	color = ft_split(line, ',');
	if (!color)
		err("Invalid RGB Format");
	i = -1;
	while (color[++i])
	{
		j = -1;
		while (color[i][++j])
			if (!ft_isdigit(color[i][j]))
				err("Invalid RGB Format");
	}
	if (i != 3)
		err("Invalid RGB Format");
	i = -1;
	while (color[++i])
		free(color[i]);
	free(color);
}

static int	parse_color(char *line)
{
	int	i;
	int	r;
	int	g;
	int	b;
	int	color;

	i = -1;
	r = 0;
	g = 0;
	b = 0;
	check_color(line);
	while (line[++i] && ft_isdigit(line[i]))
		r = r * 10 + (line[i] - '0');
	while (line[++i] && ft_isdigit(line[i]))
		g = g * 10 + (line[i] - '0');
	while (line[++i] && ft_isdigit(line[i]))
		b = b * 10 + (line[i] - '0');
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		err("Invalid RGB Format");
	color = (r * 256 * 256) + (g * 256) + b;
	return (color);
}

static char	*parse_texture(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		err("Invalid .xpm File");
	close(fd);
	return (ft_strdup(path));
}

static void	validate_line(t_map *map, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		map->tex[NO].path = parse_texture(line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		map->tex[SO].path = parse_texture(line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		map->tex[WE].path = parse_texture(line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		map->tex[EA].path = parse_texture(line + 3);
	else if (ft_strncmp(line, "F ", 2) == 0)
		map->color_floor = parse_color(line + 2);
	else if (ft_strncmp(line, "C ", 2) == 0)
		map->color_ceil = parse_color(line + 2);
	else if (ft_strchr("1 ", line[0]) != NULL)
		map->tmp_map = join_all_lines(map->tmp_map, line);
	else if (line[0] == '\n' || line[0] == '\0')
		return ;
	else
		err("Invalid File Data");
}

void	main_processing(t_map *map, char **lines)
{
	int	i;

	i = -1;
	while (lines[++i])
	{
		validate_line(map, lines[i]);
		free(lines[i]);
	}
}
