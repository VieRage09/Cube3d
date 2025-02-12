/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:52:33 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/12 18:44:51 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

// Initialize mlx basics
// Returns false on error, true is the init is done properly
t_bool	init_s_mlx(t_mlx *s_mlx)
{
	s_mlx->mlx = mlx_init();
	if (!s_mlx->mlx)
		return (manage_error("Failed to init mlx\n"), FALSE);
	s_mlx->mlx_win = mlx_new_window(s_mlx->mlx, 1920, 1080, "cub3D");
	if (!s_mlx->mlx_win)
		return (manage_error("Failed to init mlx window\n"),
				mlx_destroy_display(s_mlx->mlx), FALSE);
	return (TRUE);
}
