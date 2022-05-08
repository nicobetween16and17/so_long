/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 11:16:23 by niespana          #+#    #+#             */
/*   Updated: 2022/04/05 11:16:24 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

char	selected(int i[3], int width, int height, unsigned int r)
{
	int	ran;

	srand(r);
	if ((i[1] == 0 || i[0] == 0 || i[1] == width - 1
			|| i[0] == height - 1) && i[1] != width)
		return ('1');
	if (i[1] == width)
		return ('\n');
	ran = (rand() % 20) + 1;
	if (ran < 16)
		return ('0');
	if (ran >= 16 && ran < 18)
		return ('1');
	if (ran >= 18 && ran < 20)
		return ('C');
	return ('E');
}

int	charachter_position(int range, int start, unsigned int r)
{
	int	*cp;
	int	i;
	int	res;

	srand(r);
	i = -1;
	cp = malloc(sizeof(int) * (range + 1));
	if (!cp)
		return (start);
	while (++i < range)
		cp[i] = (i * (start - 1)) + (rand() % range) + start;
	i = rand() % range;
	res = cp[i];
	free(cp);
	return (res);
}

void	fill_file(int height, int width, char *s, unsigned int r)
{
	int	i[3];

	i[0] = -1;
	i[2] = 0;
	while (++i[0] < height)
	{
		i[1] = -1;
		while (++i[1] < width + 1)
			s[i[2]++] = selected(i, width, height, ++r);
	}
	s[i[2]] = 0;
	s[charachter_position(height - 2, width + 2, r)] = 'P';
}

void	generate_random_map(int height, int width, unsigned int r, char *name)
{
	char	*s;
	int		ran[2];
	char	*tempo;

	srand(r);
	s = malloc(sizeof(char) * ((height * (width + 1)) + 1));
	if (!s)
		return ;
	fill_file(height, width, s, r++);
	if (ft_strchr(s, 'E') == NULL)
	{
		ran[0] = charachter_position(height - 2, width + 2, r);
		while (s[ran[0]] == 'P')
			ran[0] = charachter_position(height - 2, width + 2, ++r);
		s[ran[0]] = 'E';
	}
	tempo = ft_strjoin("echo "" > ", name);
	system(tempo);
	ran[1] = open(name, O_WRONLY);
	ran[0] = -1;
	while (s[++(ran[0])])
		write(ran[1], &s[ran[0]], 1);
	free(s);
	free(tempo);
	close(ran[1]);
}

int	main(int argc, char **argv)
{
	unsigned int	r;
	char			*tempo;

	r = (unsigned int)(-1 * (long)&r);
	if (argc == 4 && ft_striteri(argv[2], &ft_isdigit)
		&& ft_striteri(argv[3], &ft_isdigit)
		&& ft_atoi(argv[2]) > 3
		&& ft_atoi(argv[3]) > 3)
		generate_random_map(ft_atoi(argv[2]), ft_atoi(argv[3]), r, argv[1]);
	else
	{
		printf("map could not be generated,try using the format %s",
			"[./a.out name x y] whereas x and y are numbers\n");
		return (0);
	}
	tempo = ft_strjoin("cat ", argv[1]);
	system(tempo);
	free(tempo);
	return (0);
}
