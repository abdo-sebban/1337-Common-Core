/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asebban <asebban@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 11:06:57 by asebban           #+#    #+#             */
/*   Updated: 2025/02/23 09:49:46 by asebban          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../get_next_line/get_next_line.h"
# include "../ft_printf/ft_printf.h"
# define TILE_SIZE 32
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124

typedef struct s_images
{
	void	*wall;
	void	*player;
	void	*collectible;
	void	*exit;
	void	*floor;
}	t_images;

typedef struct s_map
{
	char	**matrice;
	int		width;
	int		height;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_images	imgs;
	int			player_x;
	int			player_y;
	int			moves;
	int			collectibles;
	int			total_collectibles;
	int			player_count;
	int			exit_count;
	int			game_won;
}	t_game;

int		ft_strcmp(char *s1, char *s2);
int		handle_errors(int ac, char *file);
int		parse_map(t_game *game, char *filename);
int		fill_map_matrice(int fd, t_game *game);
void	free_matrice(char	**matrice, int height);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		validate_walls(t_game *game);
int		validate_map_chars(t_game *game);
int		validate_map_playability(t_game *game);
int		setup_game(t_game *game, char *file);
void	setup_hooks(t_game *game);
void	clean_game(t_game *game);
int		move_player(t_game *game, int dx, int dy);
void	image_free(t_game *game);

#endif
