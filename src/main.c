/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:56:35 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/05 21:11:05 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int main(int argc, char **argv)
{
    t_map map;
    t_game game;

    if (argc != 2)
        ft_put_err(2, "Error");
    ft_memset((void *)&game, 0, sizeof(t_game));
    game.map = &map;
    ft_memset(&map, 0, sizeof(t_map));
    parse(&map, argv[1]);
	for (int i = 0; i < map.row; i++)
	{
		printf("%s", map.map_malloc[i]);
		printf("\n");
    }
	//✅시작 위치 map->t_player posX, posY 초기화
	//✅바라보는 방향 map->t_player start_sight 초기화
	//방향 벡터 map->t_player dirX, dirY 초기화
	//카메라 평면 벡터 planeX, planeY = 0.66 초기화
	//FOV 1인친 슈팅게임에 적합한 비율(2 * atan(planeY/1.0)= 66°)
	//키보드 왼쪽 오른쪽 키는 회전 행렬
	//ESC키, red_cross_button 누르면 프로그램 종료.
	//인수는 .cub마, 맵 구성은 NSEW 0 1 문자로만
}

void	init(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_put_err();
	game->win = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->win)
		ft_put_err();
	game->img = mlx_init();
	img init하는거 질문
	
}