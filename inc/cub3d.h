/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:41:34 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/07 21:09:30 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/libft/libft.h"
# include "../lib/minilibx_opengl_20191021/mlx.h"
# include <math.h>
# include <string.h>

# define SCREEN_WIDTH	640
# define SCREEN_HEIGHT	480

# define WALL_WIDTH		64
# define WALL_HEIGHT	64


# define MINIMAP_SCALE	0.25

# define PI	3.14159

# define FALSE  0
# define TRUE  	1

# define EMPTY_LINE -2
# define ERROR      -1
# define SUCCESS    1

# define X_EVENT_KEY_DOWN	2
# define X_EVENT_KEY_UP		3
# define X_EVENT_KEY_EXIT   17

/* key */
# define KEY_LEFT       123
# define KEY_RIGHT      124
# define KEY_UP         126
# define KEY_DOWN       125
# define KEY_ESC        53
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_W			13
# define KEY_F			3

/* texture */
# define NO     0
# define SO     1
# define WE     2
# define EA     3

/* color */
# define FLOOR  4
# define CEIL   5

/* map */
# define MAP    6

/* etc */
# define END	7
# define SPACE_BAR 8

# define NO_COLOR       -1
# define M_UNIT			0.1
# define R_UNIT			0.1
# define BODY_UNIT		0.1	

/* pixel */
typedef struct s_img
{
	void			*img;
	char			*addr;
	int				line_len;
	int				bpp;
	int				endian;
}           t_img;

/* player */

typedef struct s_player
{
	double	posX;
	double	posY;
	char	start_sight;
}           t_player;

typedef struct s_camera
{
	double	dirx;
	double	diry;
}			t_camera;

/* texture */
typedef struct s_texture
{
	char			*path;
	unsigned int	*data;
	t_img			texture;
	int				width;
	int				height;
}           t_texture;

/* map */
typedef struct s_map
{
	// process_lines
	int			floor_color;
	int			ceil_color;
	char		*tmp_map_malloc;
	
	// parse_map
	char		**map_malloc;
	t_texture	tex[4];
	int			row;
	int			col;
	t_player	player;
}           t_map;

/* Structure for the game state */
typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	*map;
	t_img	wall;
	t_img	screen;
	t_img	minimap;

	int		mousemode;
	bool	w;
	bool	a;
	bool	s;
	bool	d;
	bool	l;
	bool	r;

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

	double	step;
	double	texpos;
	int		miniw;
	int		minih;
	int		gridw;
	int		gridh;
}           t_game;


/* parse */
void    parse(t_map *map, char *argv);
void	parse_map(t_map *map);
void	process_lines(t_map *map, char **lines);

void	dfs(int x, int y, t_map *map, int **visited);

/*	init */
void	init_game(t_game *game);

/* utils */
int 	ft_put_err(char *s);
void	free_all(t_map *map);
void	free_split(char **split);
void	err(t_map *map, char *message);

#endif