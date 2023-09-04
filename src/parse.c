/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 20:01:53 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/04 14:36:34 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char    *join_map_data(char *map_data, char *s2)
{
    char    *join_map;
    char    *result;

    if (map_data == NULL)
        join_map = ft_strdup("");
    else
        join_map = ft_strjoin(map_data, "\n");
    result = ft_strjoin(join_map, s2);
    if (map_data != NULL)
        free(map_data);
    free(join_map);
    return (result);
}

static void	save_map(t_map *map, int validate, char *line)
{
    if (validate == NO)
        map->tex[NO].tex_path_malloc = ft_strdup(line + 3);
    else if (validate == SO)
        map->tex[SO].tex_path_malloc = ft_strdup(line + 3);
    else if (validate == WE)
        map->tex[WE].tex_path_malloc = ft_strdup(line + 3);
    else if (validate == EA)
        map->tex[EA].tex_path_malloc = ft_strdup(line + 3);
    else if (validate == FLOOR)
        map->floor_color = parse_color(map, line, FLOOR);
    else if (validate == CEIL)
        map->ceil_color = parse_color(map, line, CEIL);
    else if (validate == MAP)
        map->tmp_map_malloc = join_map_data(map->tmp_map_malloc, line);
    else if (validate == EMPTY_LINE)
        map->tmp_map_malloc = join_map_data(map->tmp_map_malloc, line);
    else if (validate == ERROR)
        exit_error(map, "Invalid Data");
	else
        exit_error(map, "Unexpected validate value");
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
    if (ft_strchr("01EWSN ", line[0]) != NULL)
        return (MAP);
    if (line[0] == '\n')
        return (EMPTY_LINE);
    if (line[0] == '\0')
        return (END);
    return (ERROR);
}

static int is_argv_valid(t_map *map, char *argv)
{
    int     fd;

    if (ft_strncmp(argv + ft_strlen(argv) - 4, ".cub", 4))
        return (ft_put_error(2, "Error"));
    fd = open(argv, O_RDONLY);
    if (fd == -1)
        return (ft_put_error(2, "Error"));
    return (fd);
}

static void read_file(t_map *map, int fd, char **all_lines)
{
    char *line;

    line = get_next_line(fd);
    while (line)
    {
        *all_lines = join_map_data(*all_lines, line);
        free(line);
        line = get_next_line(fd);
    }
}

static void process_lines(t_map *map, char **lines)
{
    int i = -1;

    while (lines[++i])
    {
        save_map(map, validate_map_line(lines[i]), lines[i]);
        free(lines[i]);
    }
}

void parse(t_map *map, char *argv)
{
    int fd;
    char *all_lines;
    char **lines;

    map->ceil_color = NO_COLOR;
    map->floor_color = NO_COLOR;
    all_lines = NULL;
    fd = is_argv_valid(map, argv);
    read_file(map, fd, &all_lines);
    lines = ft_split(all_lines, '\n');
    free(all_lines);
    process_lines(map, lines);
    free(lines);
    parse_map(map);
    close(fd);
}