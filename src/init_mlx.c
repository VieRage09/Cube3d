/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:52:33 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/11 20:20:21 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub3D.h"

// Initialize mlx basics
// Returns false on error, true is the init is done properly
t_bool	init_s_mlx(t_mlx *s_mlx)
{
	s_mlx->mlx = mlx_init();
	if (!s_mlx->mlx)
		return (FALSE);
	ft_printf("mlx pointer init with success !\n");
	s_mlx->mlx_win = mlx_new_window(s_mlx->mlx, 1920, 1080, "cub3D");
	if (!s_mlx->mlx_win)
		return (mlx_destroy_display(s_mlx->mlx), FALSE);
	ft_printf("mlx_win pointer init with success !\n");
	return (TRUE);
}
