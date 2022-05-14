/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niespana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 11:20:35 by niespana          #+#    #+#             */
/*   Updated: 2022/05/04 11:20:39 by niespana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include <pthread.h>


typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		img_width;
	int		img_height;
}	t_data;

typedef struct s_position
{
	int	x;
	int	y;
}	t_position;

typedef struct s_map
{
	char		**map;
	int			nb_collectibles;
	t_position	*exits;
	t_data		*images;
	int			height;
	int			width;
	int			data_size;
}	t_map;

typedef struct s_player
{
	int			nb_collectibles;
	t_position	cp;
	int			nb_mooves;
	int 		hp;
}	t_player;

typedef struct	s_vars {
	void		*mlx;
	void		*win;
	t_player	player;
	t_map		map;
	int			t_v;
	int			t_h;
}	t_vars;

typedef struct s_args
{
	t_vars	vars;
	int		i;
	int		j;
}	t_args;

int			ft_printf(const char *p, ...);
int			ft_print_hex(unsigned int s, int cas);
int			*ft_putnbr_base(unsigned long s, char *base, int *res);
int			ft_putnbr_fd(long n, int fd, int unsign, int *res);
int			ft_putstr_fd(char *s, int fd);
int			ft_putchar_fd(char c, int fd, int *res);
int			ft_print_ptr(void *s);
char		*get_next_line(int fd);
int			does_contain(char *s, char c);
int			ft_strjoin(char **s1, char const *s2);
int			ft_get_start(char *s);
void		ft_strdup(char **s1, const char *s2);
char		*ft_strcpy(char *s, char *s2);
char		**ft_split(char const *s, char c);
char		**get_map(char *lines);
int			nb_collectible(t_map map);
t_position	*exits(char **map);
int			is_exit(t_position player, t_position *list);
int			mc_error(void);
int			no_exit_error(void);
int			map_error(void);
int			wall_error(void);
int			argument_error(void);
void		free_map_array(char **map);
int 		check_error(t_map *map);
int 		init_game(t_player *player, t_map map);
void		handle_input(int keycode, t_map *map, t_player *player, t_vars *vars);
void 		end_game(t_map map);
void		display_map(t_vars *vars, char **map, char next);
int			random_in_range(int a, int range, int start);
void		ft_bzero(void *b, size_t length);
int			possible_moove(int key, char **map, t_position pos);
int			put_it(t_vars *vars, t_position pos, int img);
t_position	new_pos(int x, int y);
void		firing(int key, t_vars *v);

#endif
