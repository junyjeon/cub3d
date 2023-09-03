/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:56:35 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/03 19:51:47 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int main(int argc, char **argv)
{
    t_map map;
    t_game game;

    if (argc != 2)
        ft_put_error(2, "Error");
    ft_memset((void *)&game, 0, sizeof(t_game));
    game.map = &map;
    ft_memset(&map, 0, sizeof(t_map));
    parse(&map, argv[1]);
	for (int i = 0; i < map.row; i++)
	{
		printf("%s", map.map_malloc[i]);
		printf("\n");
    }
	
} 