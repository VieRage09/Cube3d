/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:50:23 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/11 21:17:30 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Supposed to free all the inside of s_map but not the struct
void	free_s_map(t_map *s_map)
{
	free(s_map->s_texture.NO);
	free(s_map->s_texture.SO);
	free(s_map->s_texture.EA);
	free(s_map->s_texture.WE);
	free(s_map->s_texture.floor);
	free(s_map->s_texture.ceiling);
	ft_free_tab((void **)s_map->map_tab);
}

void	free_global_exit(t_global *s_global, int exit_status)
{
	free_s_map(s_global->s_map);
	mlx_destroy_window(s_global->s_mlx->mlx, s_global->s_mlx->mlx_win);
	mlx_destroy_display(s_global->s_mlx->mlx);
	free(s_global->s_mlx->mlx);
	free(s_global->s_map);
	free(s_global->s_mlx);
	exit(exit_status);
}