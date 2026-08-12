/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 17:38:07 by asebban           #+#    #+#             */
/*   Updated: 2025/08/08 05:30:56 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <mlx.h>
# include <fcntl.h>

# define RED    "\x1b[31m"
# define RESET  "\x1b[0m"

typedef struct s_line_node
{
	char				*line;
	struct s_line_node	*next;
}	t_line_node;

# define PLAYER_SQUARE_SIZE 4
# define MINI_MAP_WINDOW_WIDTH 20
# define MINI_MAP_WINDOW_HEIGHT 20
# define MINI_TILE_SIZE 5
# define MINI_MAP_OFFSET_X 10
# define MINI_MAP_OFFSET_Y 15
# define KEY_ESC 53
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_F 3
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define TEX_SIZE 64
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define NORTH_TEX 0
# define SOUTH_TEX 1
# define WEST_TEX 2
# define EAST_TEX 3

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_parsing
{
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	int			floor_color;
	int			ceiling_color;
	char		**map;
	int			map_width;
	int			map_height;
	t_vector	player_pos;
	char		player_dir;
}	t_parsing;

typedef struct s_texture
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	double		move_speed;
	double		rot_speed;
}	t_player;

typedef struct s_ray
{
	t_vector	dir;
	t_vector	side_dist;
	t_vector	delta_dist;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	double		wall_x;
	int			tex_x;
	double		step;
	double		tex_pos;
}	t_ray;

typedef struct s_keys
{
	int	shot;
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	esc;
	int	f;
}	t_keys;

typedef struct s_image
{
	void	*img;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			screen_width;
	int			screen_height;
	int			draw_start;
	int			draw_end;
	int			line_height;
	t_texture	textures[15];
	int			floor_color;
	int			ceiling_color;
	char		**map;
	int			**door_status;
	int			map_width;
	int			map_height;
	t_player	player;
	t_ray		ray;
	t_keys		keys;
	t_image		screen;
	int			running;
	double		frame_time;
	double		old_time;
	t_parsing	*parsing;
}	t_game;

typedef struct s_scan
{
	char		**map_lines;
	int			height;
	int			width;
	t_parsing	*p;
	bool		*player_found;
}	t_scan;

void	free_textures(t_parsing *p);
bool	ft_parsing(const char *filename, t_parsing *parsing);
bool	is_door_valid(char **map_lines, int x, int y);
bool	is_texture_line(const char *line);
bool	line_is_empty(const char *line);
void	ft_free_split(char **split);
bool	set_texture_path(char *line, t_parsing *p);
bool	file_has_xpm_extension(const char *path);
bool	set_ceiling_color(char *line, t_parsing *p);
bool	set_floor_color(char *line, t_parsing *p);
bool	ft_str_isnumeric(const char *s);
bool	split_rgb(const char *s, int rgb[3]);
bool	allocate_map_matrix(char **raw_map_lines,
			int map_line_count, int max_width, t_parsing *p);
bool	check_interior_leaks(char **map_lines, int height, int width);
bool	scan_and_locate_player(char **map_lines, int height, \
	int width, t_parsing *p);
void	ft_initialisation(t_parsing *p);
int		ft_init_game(t_game *game, t_parsing *parsing);
int		ft_game_loop(t_game *game);
void	cleanup_game(t_game *game);
int		close_game(t_game *game);
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	update_player(t_game *game);
void	cast_rays(t_game *game);
void	my_mlx_pixel_put(t_image *img, int x, int y, int color);
void	init_ray_dir(t_game *game, int x);
void	init_delta_dist(t_game *game);
void	init_first_step(t_game *game);
void	perform_dda(t_game *game);
void	calc_player_to_wall(t_game *game);
void	calc_wall_line(t_game *game);
void	rotate_player(t_game *game, double angle);
void	draw_minimap(t_game *game);
int		init_player(t_game *game, t_parsing *parsing);
int		select_texture(t_game *game);
void	ft_print_error(const char *msg);
bool	ft_parse_header(int fd, t_parsing *parsing, char **first_line);
bool	ft_collect(int fd, char *first_line,
			char ***out_lines, int *num_lines);
bool	ft_parse_map(int fd, char *first_map_line, t_parsing *p);
bool	is_valide_map(char **map_lines, int height, int width, t_parsing *p);
void	free_door_status(t_game *game, int rows);
void	init_keys(t_keys *keys, t_game *game);
void	handle_door_interaction(t_game *game);
void	calculate_corners(t_vector new_pos, int corners[4][2]);
#endif