/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 19:44:17 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/04 06:01:22 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int    parse_color(t_map *map, char *line, int validate)
{
    int		i;
	int		j;
	int     color;
    char    **rgb;

    rgb = ft_split(line + 2, ',');
    if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
        exit_error(map, "Invalid Color");
	j = -1;
	while (rgb[++j])
	{
		i = -1;
		while (rgb[j][++i])
			if (!ft_isdigit(rgb[j][i]))
				exit_error(map, "Invalid Color");
    }
    color = ft_atoi(rgb[0]) * 256 * 256 + ft_atoi(rgb[1]) * 256 + ft_atoi(rgb[2]);
    if (color <= 0 || color > 0xFFFFFF)
        exit_error(map, "Invalid Color");
    free_split(rgb);
    return (color);
}