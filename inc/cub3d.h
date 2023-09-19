/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:41:34 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/20 01:56:28 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <math.h>
# include <string.h>
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/libft/libft.h"
# include "../lib/minilibx_opengl_20191021/mlx.h"

# define SCREEN_WIDTH	640
# define SCREEN_HEIGHT	480

# define TEX_WIDTH		64
# define TEX_HEIGHT		64

# define X_EVENT_KEY_DOWN	2
# define X_EVENT_KEY_UP		3
# define X_EVENT_KEY_EXIT   17

/* key */
# define K_ESC		53
# define K_SFT		257

# define K_LEFT		123
# define K_RIGHT	124
# define K_UP		126
# define K_DOWN		125

# define K_A		0
# define K_S		1
# define K_D		2
# define K_W		13

# define FALSE  0
# define TRUE  	1

/* texture */
# define NO     0
# define SO     1
# define WE     2
# define EA     3
# define FLOOR  4
# define CEIL   5
# define MAP    6
# define END	7

# define R_UNIT			0.05

/* pixel */
typedef struct s_img
{
	void	*img;
	int		*data;
	int		line_len;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}			t_img;

/* player */
typedef struct s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	char	start_sight;
}			t_player;

/* texture */
typedef struct s_texture
{
	t_img	texture;
	char	*path;
	char	*data;
	int		width;
	int		height;
}			t_texture;

/* map */
typedef struct s_map
{
	t_texture	tex[4];
	t_player	player;
	int			**visited;
	char		**map;
	char		*tmp_map;
	int			color_floor;
	int			color_ceil;
	int			row;
	int			col;
	int			*row_len;
}			t_map;

/* Structure for the game state */
typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	screen;

	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	l;
	bool	r;
	bool	sft;

	double	px;
	double	py;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;

	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;

	int		lineheight;
	int		drawstart;
	int		drawend;
	double	wallx;
	int		texx;
	int		texy;
	int		texnum;
	double	step;
	double	texpos;

	int		buf[SCREEN_HEIGHT][SCREEN_WIDTH];
	int		re_buf;
	int		**texture;
	int		color;
	double	speed;
}			t_game;

/* parse */
void		parse(t_map *map, char *argv);
char		*join_all_lines(char *map_data, char *s2);
void		main_processing(t_map *map, char **lines);
void		parse_map(t_map *map);
void		check_cover_wall(t_map *map);

/* init */
void		init(t_game *g);
void		init_map(t_game *game);

/* texture */
void		init_texture(t_game *g);

/* keyhook */
int			my_mlx_keyhook(t_game *g);
void		move_w(t_game *g);
void		move_a(t_game *g);
void		move_s(t_game *g);
void		move_d(t_game *g);

/* move */
void		event_rotation(t_game *g);
void		event_move(t_game *g);

/* loop */
int			loop(t_game *g);
void		prevent_fisheye_lens(t_game *g);
void		calc_wall(t_game *g);
void		set_vertical_line(t_game *g, int x);
void		dda(t_game *g);

/* utils */
int			ft_put_err(char *s);
void		err(t_map *map, char *message);
void		check_argc(int argc);
void		free_split(char **split);

#endif
