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

t_data	*data_init2(t_data *i, int w, int h, void *mlx)
{
	i[22].img = mlx_xpm_file_to_image(mlx, "img/boir/wall_down.xpm", &w, &h);
	i[23].img = mlx_xpm_file_to_image(mlx, "img/boir/wall_left.xpm", &w, &h);
	i[24].img = mlx_xpm_file_to_image(mlx, "img/boir/wall_right.xpm", &w, &h);
	i[25].img = mlx_xpm_file_to_image(mlx, "img/boir/collectible.xpm", &w, &h);
	i[26].img = mlx_xpm_file_to_image(mlx, "img/boir/exit_close.xpm", &w, &h);
	i[27].img = mlx_xpm_file_to_image(mlx, "img/boir/ui_heart.xpm", &w, &h);
	i[28].img = mlx_xpm_file_to_image(mlx, "img/boir/ui_heart2.xpm", &w, &h);
	i[29].img = mlx_xpm_file_to_image(mlx, "img/boir/ui_heart3.xpm", &w, &h);
	i[30].img = mlx_xpm_file_to_image(mlx, "img/boir/tears.xpm", &w, &h);
	return (i);
}

t_data	*data_init(t_data *i, int w, int h, void *mlx)
{
	i = malloc(30 * sizeof(t_data));
	i[0].img = mlx_xpm_file_to_image(mlx, "img/boir/poop_f1.xpm", &w, &h);
	i[1].img = mlx_xpm_file_to_image(mlx, "img/boir/wall1.xpm", &w, &h);
	i[2].img = mlx_xpm_file_to_image(mlx, "img/boir/wall2.xpm", &w, &h);
	i[3].img = mlx_xpm_file_to_image(mlx, "img/boir/floor.xpm", &w, &h);
	i[4].img = mlx_xpm_file_to_image(mlx, "img/boir/floor.xpm", &w, &h);
	i[5].img = mlx_xpm_file_to_image(mlx, "img/boir/floor.xpm", &w, &h);
	i[6].img = mlx_xpm_file_to_image(mlx, "img/boir/standing_d.xpm", &w, &h);
	i[7].img = mlx_xpm_file_to_image(mlx, "img/boir/standing_d.xpm", &w, &h);
	i[8].img = mlx_xpm_file_to_image(mlx, "img/boir/standing_d.xpm", &w, &h);
	i[9].img = mlx_xpm_file_to_image(mlx, "img/boir/standing_d.xpm", &w, &h);
	i[10].img = mlx_xpm_file_to_image(mlx, "img/boir/standing_d.xpm", &w, &h);
	i[11].img = mlx_xpm_file_to_image(mlx, "img/boir/standing_d.xpm", &w, &h);
	i[12].img = mlx_xpm_file_to_image(mlx, "img/boir/i_floor_u.xpm", &w, &h);
	i[13].img = mlx_xpm_file_to_image(mlx, "img/boir/i_floor_d.xpm", &w, &h);
	i[14].img = mlx_xpm_file_to_image(mlx, "img/boir/i_floor_l", &w, &h);
	i[15].img = mlx_xpm_file_to_image(mlx, "img/boir/i_floor_r", &w, &h);
	i[16].img = mlx_xpm_file_to_image(mlx, "img/boir/Wcorner_UL.xpm", &w, &h);
	i[17].img = mlx_xpm_file_to_image(mlx, "img/boir/Wcorner_UR.xpm", &w, &h);
	i[18].img = mlx_xpm_file_to_image(mlx, "img/boir/Wcorner_DL.xpm", &w, &h);
	i[19].img = mlx_xpm_file_to_image(mlx, "img/boir/Wcorner_DR.xpm", &w, &h);
	i[20].img = mlx_xpm_file_to_image(mlx, "img/boir/exit_open.xpm", &w, &h);
	i[21].img = mlx_xpm_file_to_image(mlx, "img/boir/wall_up.xpm", &w, &h);
	return (data_init2(i, w, h, mlx));
}

int	destroy(int keycode, t_vars *vars)
{
	(void)keycode;
	(void)vars;
	ft_printf("endgame\n");
	system("ps -a|grep afplay|grep -v 'grep'|awk '{print $1}'|xargs kill -15");
	exit(0);
}

int	key_hook(int keycode, t_vars *vars)
{
	handle_input(keycode, &(vars->map), &(vars->player), vars);
	if ((is_exit(vars->player.cp, vars->map.exits)
			&& vars->player.nb_collectibles == vars->map.nb_collectibles)
		|| keycode == 53)
	{
		end_game(vars->map);
		destroy(keycode, vars);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	system("afplay sound/the_caves.wav &");
	if (argc != 2)
		return (argument_error());
	vars.map.map = get_map(argv[1]);
	if (!vars.map.map)
		return (-1);
	vars.map.nb_collectibles = nb_collectible(vars.map);
	vars.map.exits = exits(vars.map.map);
	if (check_error(&(vars.map)) == -1)
		return (-1);
	vars.map.data_size = 42;
	if (init_game(&vars.player, vars.map) == -1)
		return (-1);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, vars.map.width * vars.map.data_size,
			vars.map.height * vars.map.data_size, "so_long");
	vars.map.images = data_init(vars.map.images,
			vars.map.data_size, vars.map.data_size, vars.mlx);
	display_map(&vars, vars.map.map, 0);
	mlx_hook(vars.win, 17, 0, destroy, &vars);
	mlx_hook(vars.win, 2, 0, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
