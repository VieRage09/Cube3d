/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lberne <lberne@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:15:35 by tlebon            #+#    #+#             */
/*   Updated: 2025/04/23 23:15:01 by lberne           ###   ########.fr       */
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

bool	validate_enclosure(char **map, int i, int j, t_map *s_map)
{
	bool	up;
	bool	down;
	bool	left;
	bool	right;

	if (i < 0 || j < 0 || i >= (int)s_map->height || j >= (int)s_map->width)
		return (false);
	if (map[i][j] == '1' || map[i][j] == 'x')
		return (true);
	if (map[i][j] == ' ' || map[i][j] == '\0')
		return (false);
	map[i][j] = 'x';
	up = validate_enclosure(map, i - 1, j, s_map);
	down = validate_enclosure(map, i + 1, j, s_map);
	left = validate_enclosure(map, i, j - 1, s_map);
	right = validate_enclosure(map, i, j + 1, s_map);
	return (up && down && left && right);
}

bool	check_loop(char **map, t_map *s_map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (!validate_enclosure(map, i, j, s_map))
				{
					ft_free_tab((void **)map);
					return (manage_error("Map is open\n"), false);
				}
			}
			j++;
		}
		i++;
	}
	return (true);
}

bool	check_map(t_map *s_map)
{
	char	**map;

	if (!s_map)
		return (false);
	map = copy_map(s_map);
	if (!map)
		return (ft_putstr_fd("Failed to copy map\n", 2), false);
	ft_printf("Final representation of the map:\n");
	print_map(s_map);
	if (!check_invalid_char(map))
	{
		ft_free_tab((void **)map);
		return (manage_error("Invalid char in the map definition\n"), false);
	}
	if (!check_loop(map, s_map))
		return (false);
	ft_free_tab((void **)map);
	return (true);
}
