/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:13:59 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/18 20:50:56 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

int	key_press(t_game *g)
{
	mlx_hook(g->win, X_EVENT_KEY_DOWN, 0, &e_keydown, g);
	mlx_hook(g->win, X_EVENT_KEY_UP, 0, &e_keyup, g);
	mlx_hook(g->win, X_EVENT_KEY_EXIT, 0, &exit_event, g->map);
	mlx_clear_window(g->mlx, g->win);
	loop(g);
	return (0);
}