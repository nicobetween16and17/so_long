/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controlls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:12:38 by niespana          #+#    #+#             */
/*   Updated: 2022/05/03 10:12:39 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	nb_exit(char **map)
{
	int	i;
	int	j;
	int	nb_exits;

	nb_exits = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
				nb_exits++;
			j++;
		}
		i++;
	}
	return (nb_exits + 1);
}

t_position	*exits(char **map)
{
	t_position	*exit_list;
	int			i;
	int			j;
	int			k;

	k = 0;
	exit_list = malloc(nb_exit(map) * sizeof(t_position));
	if (!exit_list)
		return (NULL);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'E')
			{
				exit_list[k].x = i;
				exit_list[k++].y = j;
			}
			j++;
		}
		i++;
	}
	exit_list[k].x = -1;
	return (exit_list);
}

int	is_exit(t_position player, t_position *list)
{
	int	i;

	i = 0;
	while (list[i].x != -1)
	{
		if (list[i].x == player.x && list[i].y == player.y)
			return (1);
		i++;
	}
	return (0);
}
