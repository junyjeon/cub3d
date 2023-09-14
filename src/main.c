/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:56:35 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/14 17:36:08 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"


// static int	main_loop(t_game *g)
// {
// 	int	x;

// 	mlx_clear_window(g->mlx, g->win);
// 	setscreen(g);
// 	if (g->w || g->a || g->s || g->d)
// 		move_event(g);
// 	if (g->l || g->r)
// 		rotation_event(g);
// 	x = -1;
// 	while (++x < SCREEN_WIDTH)
// 		cast_one_ray(g, x);
// 	mlx_put_image_to_window(g->mlx, g->win, g->screen.img, 0, 0);
// 	return (0);
// }

void	screen_draw(t_game *g)
{
	int	x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		g->camerax = 2 * x / (double)SCREEN_WIDTH - 1;
		g->raydirx = g->map->player.dirx + g->map->player.planex * g->camerax;
		g->raydirx = g->map->player.diry + g->map->player.planey * g->camerax;
	}
}

static void	what_is(t_game *g)
{
	g->mapx = (int)g->px;
	g->mapy = (int)g->py;
	// g->sidedistx;
	// g->sidedisty;

	//삼각형의 비율을 구한다. deltax의 밑변은 1이 고정이니까 높이는 x/y
	g->deltadistx = fabs(1 / g->raydirx);
	g->deltadisty = fabs(1 / g->raydiry);
	// g->perpwalldist; //어안렌지 방지

//x또는 y의 방향
	// g->stepx;
	// g->stepy;

	g->hit = 0; // 광선이 벽에 부딪힘
	// g->side; // 동서? 남북?
}

void	any_find(t_game *g)
{
	if (g->raydirx < 0)
	{
		g->stepx = -1;
		g->sidedistx = (g->px - g->mapx) * g->deltadistx;
	}
	else
	{
		g->stepx = 1;
		g->sidedistx = (g->mapx + 1.0 - g->px) * g->deltadistx;
	}
	if (g->raydiry < 0)
	{
		g->stepy = -1;
		g->sidedisty = (g->px - g->mapy) * g->deltadisty;
	}
	else
	{
		g->stepy = 1;
		g->sidedisty = (g->mapy + 1.0 - g->px) * g->deltadisty;
	}
}
//Todo. 다시 이해하기
void	dda(t_game *g)
{
	while (g->hit == 0)
	{
		if (g->sidedistx < g->sidedisty)
		{
			g->sidedistx += g->deltadistx;
			g->mapx += g->step;
			g->side = 0; 
		}
		else
		{
			g->sidedisty += g->deltadistx;
			g->mapy += g->stepy;
			g->side = 1;
		}
		if (g->map->map[g->mapx][g->mapy] == '1')
			g->hit = 1;
	}
}

int	ft_loop(t_game *g)
{
	mlx_clear_window(g->mlx, g->win);
	screen_draw(g);
	what_is(g);
	//광선의 x가 몇분면에 있는지 찾기
	any_find(g);
	dda(g);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	check_argc(argc);
	init_map(&game);
	parse(game.map, argv[1]);
	for (int i = 0; game.map->map[i]; i++)
		printf("%s\n", game.map->map[i]);
	init(&game);
	mlx_hook(game.win, X_EVENT_KEY_DOWN, 0, &e_keydown, &game);
	mlx_hook(game.win, X_EVENT_KEY_UP, 0, &e_keyup, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 0, &exit_event, &game.map);
	mlx_loop_hook(game.mlx, &ft_loop, &game);
	// mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
}


//✅시작 위치 map->t_player posX, posY 초기화
	//✅바라보는 방향 map->t_player start_sight 초기화
	//방향 벡터 map->t_player dirX, dirY 초기화
	//카메라 평면 벡터 planeX, planeY = 0.66 초기화
	//FOV 1인친 슈팅게임에 적합한 비율(2 * atan(planeY/1.0)= 66°)
	//키보드 왼쪽 오른쪽 키는 회전 행렬
	//ESC키, red_cross_button 누르면 프로그램 종료.
	//✅인수는 .cub마, 맵 구성은 NSEW 0 1 문자로만
	//루프
	//mlx그리는건