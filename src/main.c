/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:56:35 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/07 21:08:41 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_map(t_game *game)
{
	t_map	*map;

	ft_memset(map, 0, sizeof(t_map));
	game->map = map;
}

void	check_argc(int argc)
{
	if (argc != 2)
        ft_put_err("Error");
}

int main(int argc, char **argv)
{
    t_game game;
	
	check_argc(argc);
    init_map(&game);
	parse(game.map, argv[1]);
	init_game(&game);
	for (int i = 0; i < game.map->row; i++)
		printf("%s\n", game.map->map_malloc[i]);
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