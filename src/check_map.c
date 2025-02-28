/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:15:35 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/28 23:52:24 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Check if every char of map is a valid one (Spawn, 0, 1, INSPACE, OUTSIDE)
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

// Returns a copy of map_tab member of s_map
static char	**copy_map(t_map *s_map)
{
	char	**copy;
	int		i;
	int		j;

	copy = malloc((s_map->ysize + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	copy[s_map->ysize] = NULL;
	i = 0;
	while (s_map->map_tab[i])
	{
		copy[i] = malloc((s_map->xsize + 1) * sizeof(char));
		if (!copy[i])
			return (ft_free_tab((void **) copy), NULL);
		copy[i][s_map->xsize] = '\0';
		j = 0;
		while (s_map->map_tab[i][j])
		{
			copy[i][j] = s_map->map_tab[i][j];
			j++;
		}
		i++;
	}
	return (copy);
}

// Recursive function: If the map tile is not a wall and is surrounded by
// classic map chars (0, 1,  ), replace the tile by a wall (1) and calls
// itself on all the surrounding tiles
// It stops when all the map is filled with wall (1) or if it founds a non wall
// tile that has no neighbours (end of map) --> meaning map is not closed
static	t_bool	flood_fill(char **map, int i, int j)
{
	if (map[i][j] == '1')
		return (TRUE);
	if (map[i + 1][j] && is_actual_map(map[i + 1][j])
		&& map[i - 1][j] && is_actual_map(map[i - 1][j])
		&& map[i][j + 1] && is_actual_map(map[i][j + 1])
		&& map[i][j - 1] && is_actual_map(map[i][j - 1]))
		map[i][j] = '1';
	else
		return (FALSE);
	printf("\nFlood_fill rep = \n");
	ft_print_str_tab(map);
	return (flood_fill(map, i + 1, j) && flood_fill(map, i - 1, j) && flood_fill(map, i, j + 1) && flood_fill(map, i, j - 1));
}

// Iterates through map to find the player spawn and update s_pos value
// Returns TRUE if only one player spawned is found
// False if there are more than one or if there is no spawn
static t_bool	find_player_spawn(char **map, t_pos *s_pos)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player_spawn(map[i][j]))
			{
				s_pos->xpos = i;
				s_pos->ypos = j;
				count++;
			}
			j++;
		}
		i++;
	}
	if (count == 1)
		return (TRUE);
	return (FALSE);
}

// Copy the map_tab of s_global to test
// If there is only 1 spawn
// If all the char of the map are valid
// If the map is surrounded by walls
t_bool	check_map(t_global *s_global) // Controls NULL
{
	char	**map;
	t_pos	spawn;
	
	if (!s_global)
		return (FALSE);
	map = copy_map(s_global->s_map);
	if (!map)
		return (FALSE);
	if (!find_player_spawn(map, &spawn))
		return (manage_error("No player spawn or too many\n"), FALSE);
	if (!check_invalid_char(map))
		return (manage_error("Invalid char in the map definition\n"), FALSE);
	return(flood_fill(map, spawn.xpos, spawn.ypos));
}