/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 20:01:53 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/03 04:08:43 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

static char    *save_tmp_map(char *s1, char *s2)
{
    char    *temp;
    char    *result;

    if (s1 == NULL)
        temp = ft_strdup("");
    else
        temp = ft_strjoin(s1, "\n");
    result = ft_strjoin(temp, s2);
    if (s1 != NULL)
        free(s1);
    free(temp);
    return (result);
}

static int    parse_color(t_map *map, char *line, int validate)
{
    int     color;
    char    **rgb;

    rgb = ft_split(line + 1, ',');
    if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
        exit_error(map, "Invalid Color");
    if (!ft_isdigit(rgb[0]) || !ft_isdigit(rgb[1]) || !ft_isdigit(rgb[2]))
        exit_error(map, "Invalid Color");
    color = ft_atoi(rgb[0]) * 256 * 256 + ft_atoi(rgb[1]) * 256 + ft_atoi(rgb[2]);
    if (color <= 0 || color > 0xFFFFFF)
        exit_error(map, "Invalid Color");
    free_split(rgb);
    return (color);
}

static void save_map(t_map *map, int validate, char *line)
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
        map->tmp_map_malloc = save_tmp_map(map->tmp_map_malloc, line);
    else if (validate == EMPTY_LINE)
        map->tmp_map_malloc = save_tmp_map(map->tmp_map_malloc, line);
    else if (validate == END)
        parse_map(map);
    else if (validate == ERROR)
        exit_error(map, "Invalid Data");
}

static void process_map_data(t_map *map, int validate, char *line)
{
    if (validate == NO || validate == SO || validate == WE || validate == EA
        || validate == FLOOR || validate == CEIL)
        save_map(map, validate, line);
    else if (validate == MAP)
        save_map(map, MAP, line);
    else if (validate == EMPTY_LINE)
        save_map(map, EMPTY_LINE, line);
    else if (validate == END)
        save_map(map, END, line);
    else if (validate == ERROR)
        exit_free(map, "Invalid Data");
    else
        exit_free(map, "Unexpected validate value");
}

static int    validate_map_line(char *line)
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
    if (ft_strchr("01EWSN", line[0]) != NULL)
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

void    parse(t_map *map, char *argv)
{
    int     fd;
    char    *line;

    map->ceil_color = NO_COLOR;
    map->floor_color = NO_COLOR;
    fd = is_argv_valid(map, argv);
    line = get_next_line(fd);
    while (line)
    {
        process_map_data(map, validate_map_line(line), line);
        free(line);
        line = get_next_line(fd);
        if (line == NULL)
           exit_error(map, "Error reading file");
    }
    free(line);
    close(fd);
}