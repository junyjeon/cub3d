/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 00:43:46 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/20 03:21:40 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	rotate(t_game *g, double angle)
{
	double	tempx;
	double	tempy;

	tempx = g->dirx;
	tempy = g->diry;
	g->dirx = tempx * cos(angle) - tempy * sin(angle);
	g->diry = tempx * sin(angle) + tempy * cos(angle);
	tempx = g->planex;
	tempy = g->planey;
	g->planex = tempx * cos(angle) - tempy * sin(angle);
	g->planey = tempx * sin(angle) + tempy * cos(angle);
}

void	event_rotation(t_game *g)
{
	if (g->l)
		rotate(g, ROTATE_SPEED);
	if (g->r)
		rotate(g, -ROTATE_SPEED);
}

void	event_move(t_game *g)
{
	if (g->w)
		move_w(g);
	if (g->a)
		move_a(g);
	if (g->s)
		move_s(g);
	if (g->d)
		move_d(g);
	if (g->sft)
		g->speed = 0.25;
	if (!g->sft)
		g->speed = 0.1;
}
