/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 20:09:42 by gshim             #+#    #+#             */
/*   Updated: 2023/09/14 17:21:50 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	game_init(t_game *g)
{
	double	angle;

	g->w = false;
	g->a = false;
	g->s = false;
	g->d = false;
	g->l = false;
	g->r = false;
	g->px = g->map->player.posx;
	g->py = g->map->player.posy;
	if (g->map->player.start_sight == 'N')
		angle = M_PI;
	else if (g->map->player.start_sight == 'E')
		angle = M_PI_2;
	else if (g->map->player.start_sight == 'S')
		angle = 0;
	else
		angle = -M_PI_2;
	g->dirx = cos(angle);// 왜 -1이 아닌가.
	g->diry = sin(angle);// 왜 0이 아닌가.
	g->planex = 0.66 * cos(angle - M_PI_2);
	g->planey = 0.66 * sin(angle - M_PI_2);
	g->miniw = SCREEN_WIDTH * MINIMAP_SCALE;
	g->minih = SCREEN_HEIGHT * MINIMAP_SCALE;
	g->gridw = g->miniw / g->map->col;
	g->gridh = g->minih / g->map->row;
	g->mousemode = 0;
}


