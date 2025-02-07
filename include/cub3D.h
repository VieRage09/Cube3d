/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:03:07 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/08 00:06:41 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
					
//----------------------------------------------------------------------------//
#include "../libs/libft/includes/libft.h"
#include "../libs/minilibx/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

typedef enum	e_bool {FALSE, TRUE} t_bool;

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

t_bool	init_s_map(t_map *s_map, int fd);
t_bool	init_s_mlx(t_mlx *s_mlx);

#endif