/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 18:47:55 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/28 23:15:35 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Trims str of all char belonging to charset
// Frees the string in input(if str exists) and returns the trimmed one
char		*free_strtrim(char *str, char *charset)
{
	char	*trim;

	trim = ft_strtrim(str, charset);
	if (str)
		free(str);
	return (trim);
}

// Returns a copy of str trimmed of all trailing \n \t and spaces
// Returns NULL on error
char	*trim_trail(char *str)
{
	char	*trim;
	int		i;

	i = ft_strlen(str) - 1;
	if (i < 0)
		return (NULL);
	while (i > 0)
	{
		if (str[i] != '\n' && str[i] != ' ' && str[i] != '\t')
			break;
		i--;
	}
	trim = ft_substr(str, 0, i + 1);
	if (!trim)
		return (NULL);
	return (trim);
}

t_bool	is_player_spawn(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (TRUE);
	return (FALSE);
}

t_bool	is_actual_map(char c)
{
	if (c == '0' || c == '1' || is_player_spawn(c) || c == INSPACE) // Rajouter INSPACE ?
		return (TRUE);
	return (FALSE);
}

t_bool	is_valid(char c)
{
	if (is_actual_map(c) || c == INSPACE || c == OUTSIDE)
		return (TRUE);
	return (FALSE);
}
