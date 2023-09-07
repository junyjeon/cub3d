/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 20:01:53 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/07 21:11:28 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	*join_all_lines(char *map_data, char *s2)
{
    char    *join_map;
    char    *all_line;

	if (!map_data)
		return s2;
	char *temp = ft_strjoin(map_data, "\n");
	all_line = ft_strjoin(temp, s2);
	free(temp);
	return all_line;
}

static void	read_file(int fd, char **all_lines)
{
    char *line;

    line = get_next_line(fd);
    while (line)
    {
        *all_lines = join_all_lines(*all_lines, line);
        free(line);
        line = get_next_line(fd);
    }
    free(line);
	close(fd);
}

static int check_file_extension(t_map *map, char *argv)
{
    int     fd;

    if (ft_strncmp(argv + ft_strlen(argv) - 4, ".cub", 4))
        return (ft_put_err("Error"));
    fd = open(argv, O_RDONLY);
    if (fd == -1)
        return (ft_put_err("Error"));
    return (fd);
}

char	**preprocessing(t_map *map, char *argv)
{
	int		fd;
    char	**lines;
    char	*all_lines;
	
    all_lines = NULL;
    fd = check_file_extension(map, argv);
    read_file(fd, &all_lines);
    lines = ft_split(all_lines, '\n');
	free(all_lines);
	return (lines);
}

void parse(t_map *map, char *argv)
{
    char **NSWEFCM;

	NSWEFCM = preprocessing(map, argv);
    process_lines(map, NSWEFCM);
    free(NSWEFCM);
    parse_map(map);
}