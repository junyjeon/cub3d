/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 17:00:08 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/19 17:00:22 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	load_texture(t_game *g, int *texture, char *path, t_img *img)
{
	int	x;
	int	y;

	img->img = mlx_xpm_file_to_image(g->mlx, path, &img->width, &img->height);
	if (!img->img)
		err(g->map, "Invalid xpm file image");
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, \
	&img->line_len, &img->endian);
	if (!img->data)
		err(g->map, "Invalid xpm file data");
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
			texture[img->width * y + x] = img->data[img->width * y + x];
	}
	mlx_destroy_image(g->mlx, img->img);
}

void	init_texture(t_game *g)
{
	t_img	image;
	int		i;

	g->texture = (int **)malloc(sizeof(int *) * 5);
	if (!g->texture)
		err(g->map, "Texture malloc failed.");
	i = -1;
	while (++i < 4)
	{
		g->texture[i] = (int *)ft_calloc(TEX_HEIGHT * TEX_WIDTH, sizeof(int));
		if (!g->texture[i])
			err(g->map, "Texture malloc failed.");
		load_texture(g, g->texture[i], g->map->tex[i].path, &image);
	}
	g->texture[4] = NULL;
}
