/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 10:12:45 by niespana          #+#    #+#             */
/*   Updated: 2022/05/03 10:12:45 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_data 	*data_init(t_data *images, int w, int h, void *mlx)
{
	images = malloc(22 * sizeof(t_data));
	images[0].img = mlx_xpm_file_to_image(mlx, "img/walls2.xpm", &w, &h);
	images[1].img = mlx_xpm_file_to_image(mlx, "img/walls.xpm", &w, &h);
	images[2].img = mlx_xpm_file_to_image(mlx, "img/wall3.xpm", &w, &h);
	images[3].img = mlx_xpm_file_to_image(mlx, "img/sol_1.xpm", &w, &h);
	images[4].img = mlx_xpm_file_to_image(mlx, "img/sol_2.xpm", &w, &h);
	images[5].img = mlx_xpm_file_to_image(mlx, "img/sol_3.xpm", &w, &h);
	images[6].img = mlx_xpm_file_to_image(mlx, "img/sprite5.xpm", &w, &h);
	images[7].img = mlx_xpm_file_to_image(mlx, "img/sprite6.xpm", &w, &h);
	images[8].img = mlx_xpm_file_to_image(mlx, "img/sprite1.xpm", &w, &h);
	images[9].img = mlx_xpm_file_to_image(mlx, "img/sprite2.xpm", &w, &h);
	images[10].img = mlx_xpm_file_to_image(mlx, "img/sprite3.xpm", &w, &h);
	images[11].img = mlx_xpm_file_to_image(mlx, "img/sprite4.xpm", &w, &h);
	images[12].img = mlx_xpm_file_to_image(mlx, "img/border1.xpm", &w, &h);
	images[13].img = mlx_xpm_file_to_image(mlx, "img/border2.xpm", &w, &h);
	images[14].img = mlx_xpm_file_to_image(mlx, "img/border3.xpm", &w, &h);
	images[15].img = mlx_xpm_file_to_image(mlx, "img/border4.xpm", &w, &h);
	images[16].img = mlx_xpm_file_to_image(mlx, "img/coin1.xpm", &w, &h);
	images[17].img = mlx_xpm_file_to_image(mlx, "img/coin2.xpm", &w, &h);
	images[18].img = mlx_xpm_file_to_image(mlx, "img/coin3.xpm", &w, &h);
	images[19].img = mlx_xpm_file_to_image(mlx, "img/coin4.xpm", &w, &h);
	images[20].img = mlx_xpm_file_to_image(mlx, "img/exit.xpm", &w, &h);
	images[21].img = mlx_xpm_file_to_image(mlx, "img/collectible.xpm", &w, &h);
	return (images);
}

int	key_hook(int keycode, t_vars *vars)
{
	if ((!is_exit(vars->player.current_position, vars->map.exits)
		   && vars->player.nb_collectibles != vars->map.nb_collectibles)
		   || keycode == 53)
	{
		end_game(vars->map);
		exit(1);
	}
	handle_input(keycode, &(vars->map), &(vars->player), *vars);
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		return (argument_error());
	vars.map.map = get_map(argv[1]);
	if (!vars.map.map)
		return (-1);
	vars.map.nb_collectibles = nb_collectible(vars.map);
	vars.map.exits = exits(vars.map.map);
	if (check_error(&(vars.map)) == -1)
		return (-1);
	vars.map.data_size = 18;
	if (init_game(&vars.player, vars.map) == -1)
		return (-1);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.map.height * vars.map.data_size,
		vars.map.width * vars.map.data_size, "so_long");
	vars.map.images = data_init(vars.map.images,
		vars.map.data_size, vars.map.data_size, vars.mlx);
	display_map(vars, vars.map.map);
	mlx_key_hook(vars.win, key_hook, &vars);
	return (0);
}
