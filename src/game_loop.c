/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 20:35:08 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/12 19:02:56 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	cross_hook(t_global *s_global)
{
	free_global_exit(s_global, EXIT_SUCCESS);
	return (0);
}

int	handle_keyhook(int keycode, t_global *s_global)
{
	if (keycode == ESCAPE)
		free_global_exit(s_global, EXIT_SUCCESS);
	return (0);
}

void	game_loop(t_global *s_global)
{
	mlx_hook(s_global->s_mlx->mlx_win, 17, 0, cross_hook, s_global);
	mlx_hook(s_global->s_mlx->mlx_win, 3, 1L << 1, handle_keyhook, s_global);
	mlx_loop(s_global->s_mlx->mlx);
}
