/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:09:30 by niespana          #+#    #+#             */
/*   Updated: 2022/05/04 10:09:32 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	possible_moove(int key, char **map, t_position pos)
{
	if (key == 13)
		return (map[pos.x + 1][pos.y] != '1');
	if (key == 0)
		return (map[pos.x][pos.y + 1] != '1');
	if (key == 2)
		return (map[pos.x][pos.y - 1] != '1');
	if (key == 1)
		return (map[pos.x - 1][pos.y] != '1');
	return (0);
}
void	put_it(t_vars vars, t_position pos, int img)
{
	ft_printf("test3 %d %d \n", vars.map.data_size, img);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.map.images[img].img,
		pos.x * vars.map.data_size, pos.y * vars.map.data_size);
}
void	set_image(t_vars vars, t_position pos, char c)
{
	srand((unsigned int)(-1 * (long)&pos.x));
	if (c == '1' && pos.x == 0 && pos.y == vars.map.width - 1)
		put_it(vars, pos, 16);
	if (c == '1' && pos.x == 0 && pos.y == 0)
		put_it(vars, pos, 18);
	if (c == '1' && pos.x == vars.map.height - 1 && pos.y == 0)
		put_it(vars, pos, 17);
	if (c == '1' && pos.x == vars.map.height - 1 && pos.y == vars.map.width - 1)
		put_it(vars, pos, 19);
	if (c == '1' && (pos.x == 0 || pos.x == vars.map.width - 1))
		put_it(vars, pos, 0);
	if (c == '1' && (pos.y == 0 || pos.y == vars.map.height - 1))
		put_it(vars, pos, 1);
	else if (c == '1')
		put_it(vars, pos, 2);
	if (c == '0' || c == 'P')
		put_it(vars, pos, (rand() % 3) + 3);
	if (c == 'P')
		put_it(vars, pos, 6);
	if (c == 'E')
		put_it(vars, pos, 20);
	if (c == 'C')
		put_it(vars, pos, 5);
}
void	display_map(t_vars vars, char **map)
{
	t_position pos;

	pos.x = -1;
	while(map[++pos.x])
	{
		pos.y = -1;
		while (map[pos.x][++pos.y])
			set_image(vars, pos, map[pos.x][pos.y]);
	}
}

void	handle_input(int keycode, t_map *map, t_player *player, t_vars vars)
{
	ft_printf("input chosen is [%d]\n", keycode);
	if (!possible_moove(keycode, map->map, player->current_position))
		return ;
	player->nb_mooves++;
	if (keycode == 13)
		map->map[player->current_position.x][player->current_position.y] = '0';
	if (keycode == 0)
		map->map[player->current_position.x][player->current_position.y] = '0';
	if (keycode == 2)
		map->map[player->current_position.x][player->current_position.y] = '0';
	if (keycode == 1)
		map->map[player->current_position.x][player->current_position.y] = '0';
	if (keycode == 13)
		player->current_position.x -= 1;
	if (keycode == 0)
		player->current_position.y -= 1;
	if (keycode == 2)
		player->current_position.y += 1;
	if (keycode == 1)
		player->current_position.x += 1;
	if (map->map[player->current_position.x][player->current_position.y] == 'C')
		player->nb_collectibles += 1;
	map->map[player->current_position.x][player->current_position.y] = 'P';
	display_map(vars, map->map);
}
