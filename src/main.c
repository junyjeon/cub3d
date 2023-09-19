/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:56:35 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/19 17:10:04 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	check_argc(argc);
	init_map(&game);
	parse(game.map, argv[1]);
	init(&game);
	mlx_loop_hook(game.mlx, &loop, &game);
	my_mlx_keyhook(&game);
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

// 인자 수 확인
// 게임의 맵 초기화
// 제공된 파일에서 맵 데이터 파싱
/**
 * init 게임을 전체적으로 초기화 하는 함수
 * load_texture 텍스쳐 로딩
 * init_texture 게임에 사용될 텍스쳐 4개 초기화
 * init_img 스크린 이미지 초기화
 * init_mlx_win mlx, win 초기화
 * init_game 게임 관련 변수 초기화 
 */

/**
 * parse 전처리, 주요처리를 수행한 후 파싱된 맵을 반환
 * join_all_line 두 문자열을 합친 문자열을 반환
 * pre_processing 파일 확장자를 확인하고 파일의 모든 줄을 반환
 * - read_file 파일에서 한 줄씩 읽어 모든 문자열을 반환
 * - check_file_extension 파일 확장자를 확인하고 파일을 열어 파일 디스크립터를 반환
 * main_processing
 * - validate_line 각 줄의 유효성을 검증함
 * - parse_texture 텍스처 파일 경로를 파싱하고 반환
 * - parse_color RGB 색상 데이터를 파싱하고 색상 코드를 반환
 *   - check_color RGB 색상 포맷을 검증
 * parse_map
 * - parses_map_line 맵의 각 줄을 파싱하여 플레이어 위치, 방향, row, col을 결정
 *   - init_player 플레이어 위치, 방향 초기화
 * - create_visited 방문 셀을 추적하기 위한 map과 같은 2차원 배열 생성
 */

/**
 * 
 * 
 */

// 루프 로직 설정
// 키 입력 훅 설정
// 루프 실행
