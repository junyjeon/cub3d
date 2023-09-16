/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 19:41:34 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/16 20:21:25 by junyojeo         ###   ########.fr       */
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

# define MINIMAP_SCALE	1

# define FALSE  0
# define TRUE  	1

# define EMPTY_LINE -2
# define ERROR      -1
# define SUCCESS    1

# define PI		3.14159265358979323846264338327950288
# define PI_2	1.57079632679489661923132169163975144

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
	unsigned int	*data;
	int				line_len;
	int				bpp;
	int				endian;
	int				width;
	int				height;
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
	t_img			texture;
	char			*path;
	char			*data;
	int				width;
	int				height;
}			t_texture;

/* map */
typedef struct s_map
{
	t_texture	tex[4];
	t_player	player;
	char		**map;
	char		*tmp_map;
	int			color_floor;
	int			color_ceil;
	int			row;
	int			col;
}			t_map;

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
	int		texnum;

	double	step;
	double	texpos;
	int		miniw;
	int		minih;
	int		gridw;
	int		gridh;

	int		buf[SCREEN_HEIGHT][SCREEN_WIDTH];
	int		re_buf;
	int		**texture;
}			t_game;

/* parse */
void		parse(t_map *map, char *argv);
char		*join_all_lines(char *map_data, char *s2);
void		main_processing(t_map *map, char **lines);
void		parse_map(t_map *map);

void		check_cover_wall(t_map *map, int **visited);

/* init */
void		init(t_game *g);

/* loop */
int			loop(t_game *g);

/* utils */
int			ft_put_err(char *s);
void		free_all(t_map *map);
void		free_split(char **split);
void		err(t_map *map, char *message);
int			exit_event(t_map *map);

/* utils 2*/
void		init_map(t_game *game);
void		check_argc(int argc);

/* ray_casting */

// void		move(t_game *g, double angle);
// void		rotate(t_game *g, double angle);
// int			e_keydown(int key_code, t_game *game);
// int			e_keyup(int key_code, t_game *game);
// void		rotation_event(t_game *g);
// void		move_event(t_game *g);
// void		ray_cal_init(t_game *g, int x);
// void		getsidedist(t_game *g);
// void		dda(t_game *g);
// void		getdrawpoint(t_game *g);
// void		cal_texture(t_game *g, t_texture *wall_tex);
// void		cast_one_ray(t_game *g, int x);
// void		drawline(t_game *g, t_texture *wall_tex, int x);
// void		setscreen(t_game *g);
// t_texture	getwalltexture(t_game *g);

#endif