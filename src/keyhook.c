/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:13:59 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/19 01:49:42 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	moveable(t_game *game, double nx, double ny)
{
	int	x;
	int	y;

	x = (int)nx;
	y = (int)ny;
	if (x < 0 || y < 0 || x >= game->map->row || y >= game->map->col)
		return (1);
	if (game->map->map[x][y] > '0')
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

int	e_keydown(int key_code, t_game *game)
{
	printf("down\n");
	if (key_code == K_ESC)
		exit_event(game->map);
	else if (key_code == K_UP || key_code == K_W)
		game->w = true;
	else if (key_code == K_DOWN || key_code == K_S)
		game->s = true;
	else if (key_code == K_A)
		game->a = true;
	else if (key_code == K_D)
		game->d = true;
	else if (key_code == K_RIGHT)
		game->r = true;
	else if (key_code == K_LEFT)
		game->l = true;
	return (0);
}

int	e_keyup(int key_code, t_game *game)
{
	printf("up\n");
	if (key_code == K_UP || key_code == K_W)
		game->w = false;
	else if (key_code == K_DOWN || key_code == K_S)
		game->s = false;
	else if (key_code == K_A)
		game->a = false;
	else if (key_code == K_D)
		game->d = false;
	else if (key_code == K_RIGHT)
		game->r = false;
	else if (key_code == K_LEFT)
		game->l = false;
	return (0);
}

int	my_mlx_keyhook(t_game *g)
{
	mlx_hook(g->win, X_EVENT_KEY_DOWN, 0, &e_keydown, g);
	mlx_hook(g->win, X_EVENT_KEY_UP, 0, &e_keyup, g);
	mlx_hook(g->win, X_EVENT_KEY_EXIT, 0, &exit_event, g->map);
	mlx_clear_window(g->mlx, g->win);
	loop(g);
	return (0);
}
