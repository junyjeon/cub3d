/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:13:59 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/20 01:56:19 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	event_exit(void)
{
	ft_putendl_fd("EXIT CUB3D", 0);
	exit(1);
}

static int	e_keydown(int key_code, t_game *g)
{
	if (key_code == K_ESC)
		event_exit();
	else if (key_code == K_UP || key_code == K_W)
		g->w = true;
	else if (key_code == K_DOWN || key_code == K_S)
		g->s = true;
	else if (key_code == K_A)
		g->a = true;
	else if (key_code == K_D)
		g->d = true;
	else if (key_code == K_RIGHT)
		g->r = true;
	else if (key_code == K_LEFT)
		g->l = true;
	else if (key_code == K_SFT)
		g->sft = true;
	return (0);
}

static int	e_keyup(int key_code, t_game *g)
{
	if (key_code == K_UP || key_code == K_W)
		g->w = false;
	else if (key_code == K_DOWN || key_code == K_S)
		g->s = false;
	else if (key_code == K_A)
		g->a = false;
	else if (key_code == K_D)
		g->d = false;
	else if (key_code == K_RIGHT)
		g->r = false;
	else if (key_code == K_LEFT)
		g->l = false;
	else if (key_code == K_SFT)
		g->sft = false;
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
