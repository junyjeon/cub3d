/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junyojeo <junyojeo@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 03:43:21 by junyojeo          #+#    #+#             */
/*   Updated: 2023/09/19 17:09:14 by junyojeo         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	ft_put_err(char *s)
{
	write(2, "Error: ", 8);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	exit(1);
}

void	err(t_map *map, char *s)
{
	write(2, "Error: ", 8);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	(void)map;
	exit(1);
}

void	check_argc(int argc)
{
	if (argc != 2)
		ft_put_err("invalid argc count");
}

int	event_exit(void)
{
	ft_putendl_fd("EXIT CUB3D", 0);
	exit(1);
}

void	free_split(char **split)
{
	int	i;

	if (split)
	{
		i = -1;
		while (split[++i])
		{
			free(split[i]);
			split[i] = NULL;
		}
		free(split);
		split = NULL;
	}
}
