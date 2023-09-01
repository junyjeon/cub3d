/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:56:35 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/01 20:01:24 by junyojeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/cub3d.h"

int ft_putendl_fd(char *s, int fd)
{
    write(fd, s, ft_strlen(s));
    write(fd, "\n", 1);
    return (0);
}

int main(int argc, char **argv)
{
    t_map map;
    t_game game;

    if (argc != 2)
        return (ft_putendl_fd("Error", 2));
    ft_memset((void *)&game, 0, sizeof(t_game));
    game.map = &map;
    ft_memset(&map, 0, sizeof(t_map));
    parse(&map, argv[1]);
}