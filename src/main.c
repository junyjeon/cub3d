/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:56:35 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/18 20:47:24 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	check_argc(argc);
	init_map(&game);
	parse(game.map, argv[1]);
	for (int i = 0; game.map->map[i]; i++)
		printf("%s\n", game.map->map[i]);
	printf("game.map->row: %d\ngame.map->col: %d\n", game.map->row, game.map->col);
	init(&game);
	mlx_loop_hook(game.mlx, &loop, &game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, &key_press, &game);
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
