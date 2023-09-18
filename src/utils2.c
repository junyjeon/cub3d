/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 16:19:56 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/18 20:05:02 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_map(t_game *game)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	ft_memset(map, 0, sizeof(t_map));
	game->map = map;
}

void	check_argc(int argc)
{
	if (argc != 2)
		ft_put_err("invalid argc count");
}