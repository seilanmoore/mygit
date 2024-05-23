/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:50:51 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/23 12:58:10 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/include/libft.h"
# include "../minilibx-linux/mlx.h"

# include <X11/keysym.h>
# include <X11/X.h>
# include <errno.h>

# define TRUE 1
# define NONE 0
# define FALSE 0
# define SUCCESS 0
# define ERROR -1
# define TILE_SIZE 64
# define NOTVALID "Map not valid"

# define DESTROY_NOTIF 17
# define NO_EVENT_MASK 0

//Colors
# define WHITE			0x00FFFFFF
# define GRAY			0x007F7F7F
# define BLACK			0x00000000
# define RED			0x00FF0000
# define GREEN			0x0000FF00
# define BLUE			0x000000FF
# define ORANGE			0x00FF7F00
# define YELLOW			0x00FFFF00
# define SPRING_GREEN	0x0000FF7F
# define CYAN			0x0000FFFF
# define MAGENTA		0x00FF00FF
# define ROSE			0x00FF007F
# define PURPLE			0x007F00FF

typedef struct s_coord
{
	size_t	y;
	size_t	x;
}	t_coord;

typedef struct s_player
{
	t_coord	coord;
	size_t	collecs;
	size_t	moves;
}	t_player;

typedef struct s_map
{
	char	*fn;
	int		fd;
	char	**mtrx;
	size_t	width;
	size_t	height;
	size_t	collecs;
	size_t	exits;
	size_t	player;
	size_t	walls;
	size_t	spaces;
}	t_map;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

typedef struct s_texture
{
	t_img	border;
	t_img	ground;
	t_img	exit;
	t_img	collectible;
	t_img	player;
}	t_texture;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_texture	texture;
	t_map		map;
	t_player	player;
}	t_data;

//PARSE_MAP_FILE
//	parse_file
void	print_map(char **map);
void	parse_file(t_data *data, int argc, char **argv);
//	check_map
int		check_sections(t_map *map, char *line);
void	check_map(t_data *data);
//	check_path
void	get_player_coord(t_data *data, char **map);
void	check_path(t_data *data);
//	open_close_file
void	openf(t_data *data);
void	closef(t_data *data);

//GRAPHICS
//	init_window
void	init_window(t_data *data);
//		init_textures
void	convert_xpm(t_data *data);
//	draw_map
void	draw_map(t_data *data);
//	draw_sections
void	draw_ground(t_data *data, int x, int y);
void	draw_collectible(t_data *data, int x, int y);
void	draw_border(t_data *data, int x, int y);
void	draw_exit(t_data *data, int x, int y);
void	draw_player(t_data *data, int x, int y);
//check_moves
void	check_up(t_data *data, t_coord *coord);
void	check_right(t_data *data, t_coord *coord);
void	check_down(t_data *data, t_coord *coord);
void	check_left(t_data *data, t_coord *coord);
//end_game
void	end_game(t_data *data);

//UTILS
//	utils
void	print_map(char **map);
//	error
void	ft_error(t_data *data, char *message);
//	cleanup
void	free_map(char **map);
void	terminate(t_data *data);

#endif