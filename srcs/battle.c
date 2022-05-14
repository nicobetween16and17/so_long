/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:16:52 by niespana          #+#    #+#             */
/*   Updated: 2022/05/14 14:16:53 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#include <stdio.h>

void	*tear_travel(void *args)
{
	int			h;
	int			w;
	int			i;
	t_vars		*v;

	v = (t_vars *)args;
	printf("executing the thread\n");
	h = v->player.cp.x * 42;
	w = v->player.cp.y * 42;
	i = 0;
	while (i++ < 100)
	{
		if (v->t_v)
			h += v->t_h;
		else
			w += v->t_h;
		mlx_put_image_to_window(v->mlx, v->win, v->map.images[30].img, h, w);
		usleep(10000);
	}
	return (0);
}

void	add_info(t_vars *v, int i, int j)
{

	v->t_v = i;
	v->t_h = j;
}

void	firing(int key, t_vars *v)
{
	pthread_t	tear[10000];
	static int	new;

	if (key == 126)//up
		add_info(v, 0, 1);
	else if (key == 123)//left
		add_info(v, 0, -1);
	else if (key == 125)//down
		add_info(v, 1, 1);
	else if (key == 124)//right
		add_info(v, 1, -1);
	else
		return ;
	if (new == 9999)
		new = 0;
	pthread_create(&tear[new++], NULL, (void *)tear_travel, (void *)v);
	return ;
}


