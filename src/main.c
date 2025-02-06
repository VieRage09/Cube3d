/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:02:37 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/06 16:36:19 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main (int ac, char **av)
{
	if (ac != 2)
		ft_printf("Usage : ./cub3D valid_map_path\nThanks\n");
	av = NULL;
	char	*test = get_next_line(0);
	ft_printf("U typed in %s", test);
	return (0);
}