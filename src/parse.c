/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 20:01:53 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/01 23:15:24 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int is_extension_valid(char *argv)
{
    int     fd;

    if (ft_strncmp(argv + ft_strlen(argv) - 4, ".cub", 4))
        return (ft_put_error(2, "Error"));
    fd = open(argv, O_RDONLY);
    if (fd == -1)
        return (ft_put_error(2, "Error"));
    return (fd);
}

int is_map_valid(t_map *map, char *argv)
{
    if (!is_extension_valid)
        exit_error(map, "Invalid Extension");
    return (open(argv, O_RDONLY));
}

void    parse(t_map *map, char *argv)
{
    int     fd;
    char    *line;
    int     validate; // 데이터 유효성 검사 결과를 저장하는 변수

    
    map->ceil_color = ft_strdup("");
    map->floor_color = ft_strdup("");
    fd = is_map_valid(map, argv);
    if (fd == -1)
        exit_and_free(map, "Invalid Map");
    line = get_next_line(fd);
    while (line > 0)
    {
        if (line[0] != '\0')
        {
            validate = check_valid_data(line);
            if (validate == ERROR)
                exit_and_free(map, "Invalid Data");
        }
        free(line);
        line = get_next_line(fd);
    }
    save_map(map, argv);
    if (line)
        free(line);
    close(fd);
}