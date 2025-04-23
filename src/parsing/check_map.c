/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:15:35 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/23 20:20:09 by lberne           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Check if every char of map is a valid one (Spawn, 0, 1, INSPACE, OUTSIDE)
static bool	check_invalid_char(char **map)
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
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static bool	validate_enclosure(char **map, int i, int j, int height, int width)
{
    // Check if we are out of bounds
    if (i < 0 || j < 0 || i >= height || j >= width)
        return (false);

    // If we hit a wall or already visited tile, stop
    if (map[i][j] == '1' || map[i][j] == 'x')
        return (true);

    // If we hit a space or invalid character, the map is open
    if (map[i][j] == ' ' || map[i][j] == '\0')
        return (false);

    // Mark the current tile as visited
    map[i][j] = 'x';

    // Recursively check all four directions
    bool up = validate_enclosure(map, i - 1, j, height, width);
    bool down = validate_enclosure(map, i + 1, j, height, width);
    bool left = validate_enclosure(map, i, j - 1, height, width);
    bool right = validate_enclosure(map, i, j + 1, height, width);

    // Return true only if all directions are enclosed
    return (up && down && left && right);
}

bool	check_map(t_map *s_map)
{
    char	**map;
    t_pos	spawn;

    if (!s_map)
        return (false);

    // Create a copy of the map for validation
    map = copy_map(s_map);
    if (!map)
        return (ft_putstr_fd("Failed to copy map\n", 2), false);

    ft_printf("Final representation of the map:\n");
    ft_print_str_tab(s_map->map_tab);

    // Find the player's spawn point
    if (!find_player_spawn(map, &spawn))
    {
        ft_free_tab((void **)map);
        return (manage_error("No player spawn or too many\n"), false);
    }

    // Check for invalid characters
    if (!check_invalid_char(map))
    {
        ft_free_tab((void **)map);
        return (manage_error("Invalid char in the map definition\n"), false);
    }

    // Validate enclosure using flood-fill
    if (!validate_enclosure(map, spawn.ypos, spawn.xpos, s_map->height, s_map->width))
    {
        ft_free_tab((void **)map);
        return (manage_error("Map is open\n"), false);
    }

    // Free the map copy
    ft_free_tab((void **)map);
    return (true);
}
