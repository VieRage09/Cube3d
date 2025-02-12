/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:03:07 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/12 18:42:58 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
					
#include "../libs/libft/includes/libft.h"
#include "../libs/minilibx/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

typedef enum	e_bool {FALSE, TRUE} t_bool;

typedef enum	e_keycode
{
	ESCAPE = 65307
}t_keycode;

typedef enum	e_char
{
	OUTSIDE = '-',
	INSPACE = ' '
}t_char;

typedef struct	s_textures
{
	char	*NO;
	char	*SO;
	char	*EA;
	char	*WE;
	char	*floor;
	char	*ceiling;
} t_textures;

typedef struct	s_map
{
	t_textures	s_texture;
	char		**map_tab;
	size_t		xsize;
	size_t		ysize;
} t_map;

typedef struct	s_mlx
{
	void	*mlx;
	void	*mlx_win;
} t_mlx;

typedef struct s_global
{
	t_mlx	*s_mlx;
	t_map	*s_map;
}t_global;

// CHECK_MAP.C	
t_bool	check_map(t_global *s_global);

// CLEAN_UP.C
void	free_s_map(t_map *s_map);
void	free_global_exit(t_global *s_global, int exit_status);

// ERRORS.C
void	manage_error(char *str_err);

// GAME_LOOP.C
void	game_loop(t_global *s_global);

// INIT_MLX.C
t_bool	init_s_mlx(t_mlx *s_mlx);

// INIT_S_MAP.C
t_bool	init_s_map(t_map *s_map, char *path);
t_bool	init_s_mlx(t_mlx *s_mlx);

// UTILS.C
char	*free_strtrim(char *str, char *charset);
char	*trim_trail(char *str);
t_bool	is_player_spawn(char c);
t_bool	is_actual_map(char c);
t_bool	is_valid(char c);




#endif