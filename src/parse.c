/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 03:28:50 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/14 15:31:42 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

char	*join_all_lines(char *map_data, char *s2)
{
	char	*all_line;
	char	*tmp;

	if (!map_data)
		return (ft_strdup(s2));
	tmp = ft_strjoin(map_data, "\n");
	all_line = ft_strjoin(tmp, s2);
	return (all_line);
}

static void	read_file(int fd, char **all_lines)
{
	char	*line;

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

static int	check_file_extension(char *argv)
{
	int	fd;

	if (ft_strncmp(argv + ft_strlen(argv) - 4, ".cub", 4))
		return (ft_put_err("Error"));
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (ft_put_err("Error"));
	return (fd);
}

static char	**pre_processing(char *argv)
{
	int		fd;
	char	**lines;
	char	*all_lines;

	fd = check_file_extension(argv);
	all_lines = NULL;
	read_file(fd, &all_lines);
	lines = ft_split(all_lines, '\n');
	free(all_lines);
	return (lines);
}

void	parse(t_map *map, char *argv)
{
	char	**lines;

	lines = pre_processing(argv);
	main_processing(map, lines);
	free(lines);
	parse_map(map);
}
