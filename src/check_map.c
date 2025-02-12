/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:15:35 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/12 19:01:47 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_bool	check_invalid_char(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!is_valid(map[i][j]))
				return (FALSE);
			j++;
		}
		i++;
	}
	return (TRUE);
}

// static t_bool	map_is_closed(char **map)
// {
// 	int	i;
// 	int	j;
// 	int	firsti;
// 	int	firstj;

// 	firsti = 0;
// 	firstj = 0;
// 	i = firsti;
// 	j = firstj;
// 	while (1)
// 	{
// 		if (map[i][j] != 1) // pb si map[0][0] != 1 --> Rajouter un fonction qui trouve les coordonnes du premier 1 de la 1ere ligne
// 			return (FALSE);
// 		if (map[i][j + 1] && map[i][j + 1] != OUTSIDE)
// 			j++;
// 		else if (map[i + 1][j] && map[i + 1][j] != OUTSIDE)
// 			i++;
// 		else
// 		{

// 		}
// 		if (i == firsti && j == firstj)
// 			return (TRUE);
// 	}
// }

t_bool	check_map(t_global *s_global) // Controls NULL
{
	char	**map;

	map = s_global->s_map->map_tab;
	if (!check_invalid_char(map))
		return (manage_error("Invalid char in the map definition\n"), FALSE);
	// if (!map_is_closed(map))
	// 	return (manage_error("Map is not fully closed\n"), FALSE);
	return (TRUE);
}