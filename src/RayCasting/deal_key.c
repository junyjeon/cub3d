/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 21:50:11 by gshim             #+#    #+#             */
/*   Updated: 2023/09/10 21:26:46 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	moveable(t_game *game, double nx, double ny)
{
	double	x;
	double	y;

	x = nx;
	y = ny;
	if (x < 0 || y < 0 || x >= game->map->row || y >= game->map->col)
		return (1);
	//Todo. 플레이어 생성 위치 투명벽, 텍스쳐 xpm 사이즈, 색상 코드 체크
	if (game->map->map_malloc[(int)x][(int)y] == '1')
		return (0);
	else
		return (1);
}

void	move(t_game *g, double angle)
{
	double	nx;
	double	ny;

	nx = g->px + (g->dirx * cos(angle) - g->diry * sin(angle)) * M_UNIT;
	ny = g->py + (g->dirx * sin(angle) + g->diry * cos(angle)) * M_UNIT;
	if (!moveable(g, nx, ny)
		|| !moveable(g, -nx + g->planex * 0.25, ny + g->planey * 0.25)
		|| !moveable(g, nx + g->planex * 0.25, ny + g->planey * 0.25)
		|| !moveable(g, -nx + g->planex * 0.25, ny - g->planey * 0.25)
		|| !moveable(g, nx + g->planex * 0.25, ny - g->planey * 0.25))
		return ;
	g->px = nx;
	g->py = ny;
}

void	rotate(t_game *g, double angle)
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

int	e_keydown(int key_code, t_game *game)
{
	printf("keydown event\n");


	if (key_code == KEY_ESC)
		exit_event(game->map);
	else if (key_code == KEY_UP || key_code == KEY_W)
		game->w = true;
	else if (key_code == KEY_DOWN || key_code == KEY_S)
		game->s = true;
	else if (key_code == KEY_A)
		game->a = true;
	else if (key_code == KEY_D)
		game->d = true;
	else if (key_code == KEY_RIGHT)
		game->r = true;
	else if (key_code == KEY_LEFT)
		game->l = true;
	return (0);
}

int	e_keyup(int key_code, t_game *game)
{
	if (key_code == KEY_UP || key_code == KEY_W)
		game->w = false;
	else if (key_code == KEY_DOWN || key_code == KEY_S)
		game->s = false;
	else if (key_code == KEY_A)
		game->a = false;
	else if (key_code == KEY_D)
		game->d = false;
	else if (key_code == KEY_RIGHT)
		game->r = false;
	else if (key_code == KEY_LEFT)
		game->l = false;
	return (0);
}
