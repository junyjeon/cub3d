/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:02:30 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/20 00:47:15 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	moveable(t_game *g, double x, double y)
{
	double	m;

	m = 0.05;
	if (g->map->map[(int)x][(int)y] == '1')
		return (FALSE);
	else if (g->map->map[(int)(x + m)][(int)y] == '1')
		return (FALSE);
	else if (g->map->map[(int)x][(int)(y + m)] == '1')
		return (FALSE);
	else if (g->map->map[(int)(x + m)][(int)(y + m)] == '1')
		return (FALSE);
	else if (g->map->map[(int)(x - m)][(int)y] == '1')
		return (FALSE);
	else if (g->map->map[(int)x][(int)(y - m)] == '1')
		return (FALSE);
	else if (g->map->map[(int)(x - m)][(int)(y + m)] == '1')
		return (FALSE);
	else if (g->map->map[(int)(x - m)][(int)(y + m)] == '1')
		return (FALSE);
	else if (g->map->map[(int)(x + m)][(int)(y - m)] == '1')
		return (FALSE);
	return (TRUE);
}

void	move_w(t_game *g)
{
	if (moveable(g, g->px + g->dirx * g->speed, g->py))
		g->px += g->dirx * g->speed;
	if (moveable(g, g->px, g->py + g->diry * g->speed))
		g->py += g->diry * g->speed;
}

void	move_a(t_game *g)
{
	double	nx;
	double	ny;

	nx = g->dirx * cos(acos(-1) / 2) - g->diry * sin(acos(-1) / 2);
	ny = g->dirx * sin(acos(-1) / 2) + g->diry * cos(acos(-1) / 2);
	if (moveable(g, g->px + nx * g->speed, g->py))
		g->px += nx * g->speed;
	if (moveable(g, g->px, g->py + ny * g->speed))
		g->py += ny * g->speed;
}

void	move_s(t_game *g)
{
	if (moveable(g, g->px - g->dirx * g->speed, g->py))
		g->px -= g->dirx * g->speed;
	if (moveable(g, g->px, g->py - g->diry * g->speed))
		g->py -= g->diry * g->speed;
}

void	move_d(t_game *g)
{
	double	nx;
	double	ny;

	nx = g->dirx * cos(acos(-1) / 2) - g->diry * sin(acos(-1) / 2);
	ny = g->dirx * sin(acos(-1) / 2) + g->diry * cos(acos(-1) / 2);
	if (moveable(g, g->px - nx * g->speed, g->py))
		g->px -= nx * g->speed;
	if (moveable(g, g->px, g->py - ny * g->speed))
		g->py -= ny * g->speed;
}
