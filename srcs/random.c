/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:36:18 by niespana          #+#    #+#             */
/*   Updated: 2022/05/03 15:36:19 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	random_in_range(int a, int range, int start)
{
	char	c[10000];
	int		rand;
	float	f;

	if (a > 10000)
		a = a % 10000;
	rand = (int)&(c[a]);
	if (rand < 0)
		rand = -rand;
	rand = rand % 1000;
	rand = pow(rand,2);
	rand = rand % 10000;
	f = (float)rand / 10000;
	return ((int)(f * range) + start);
}
