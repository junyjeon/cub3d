/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 11:54:07 by gshim             #+#    #+#             */
/*   Updated: 2023/09/10 02:24:26 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	rotation_event(t_game *g)
{
	if (g->l)
		rotate(g, R_UNIT);
	if (g->r)
		rotate(g, -R_UNIT);
}

void	move_event(t_game *g)
{
	if (g->w)
		move(g, 0);
	if (g->a)
		move(g, M_PI_2);
	if (g->s)
		move(g, M_PI);
	if (g->d)
		move(g, -M_PI_2);
}
