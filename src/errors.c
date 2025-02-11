/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:55:43 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/11 20:19:41 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Euh pour l'instant mdr
void	manage_error(int num)
{
	if (num == 1)
	{
		ft_putstr_fd("Wrong char on map definition\n", 2);
	}
}