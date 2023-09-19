/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:13:59 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/19 17:11:35 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	e_keydown(int key_code, t_game *game)
{
	if (key_code == K_ESC)
		event_exit();
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
	mlx_hook(g->win, X_EVENT_KEY_EXIT, 0, &event_exit, g->map);
	mlx_clear_window(g->mlx, g->win);
	loop(g);
	return (0);
}
