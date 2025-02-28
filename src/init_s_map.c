/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_s_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:10:28 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/28 22:53:34 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Used to assign each texture path to its correct member inside s_map
// Returns false on error or if the texture id isn't found
static t_bool	assign_correct_attribute(char *line, t_map *s_map)
{
	if (ft_strncmp(line, "NO", 2) == 0)	
	{
		s_map->s_texture.NO = ft_strtrim(line, "NO \t");
		if (!s_map->s_texture.NO)
			return (FALSE);
	}
	else if (ft_strncmp(line, "SO", 2) == 0)	
	{
		s_map->s_texture.SO = ft_strtrim(line, "SO \t");
		if (!s_map->s_texture.SO)
			return (FALSE);
	}
	else if (ft_strncmp(line, "EA", 2) == 0)	
	{
		s_map->s_texture.EA = ft_strtrim(line, "EA \t");
		if (!s_map->s_texture.EA)
			return (FALSE);
	}
	else if (ft_strncmp(line, "WE", 2) == 0)	
	{
		s_map->s_texture.WE = ft_strtrim(line, "WE \t");
		if (!s_map->s_texture.WE)
			return (FALSE);
	}
	else if (ft_strncmp(line, "F", 1) == 0)	
	{
		s_map->s_texture.floor = ft_strtrim(line, "F \t");
		if (!s_map->s_texture.floor)
			return (FALSE);
	}
	else if (ft_strncmp(line, "C", 1) == 0)	
	{
		s_map->s_texture.ceiling = ft_strtrim(line, "C \t");
		if (!s_map->s_texture.ceiling)
			return (FALSE);
	}
	else
		return (FALSE);	
	return (TRUE);
}

// Goes through the map file until all the textures path are found
// Returns false on error or if there are missing textures
static t_bool	init_textures(t_map *s_map, int fd)
{
	int		count;
	char	*line;
	char	*trimed;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		while (line && ft_str_is_wspace(line))
		{
			free(line);
			line = get_next_line(fd);
		}
		trimed = ft_strtrim(line, " \t");
		if (!assign_correct_attribute(trimed, s_map))
			return (free(trimed), FALSE);
		free(trimed);
		count++;
		free(line);
		if (count == 6)
			break;
		line = get_next_line(fd);
	}
	if (count != 6)
		return (FALSE);
	return (TRUE);
}

// Skip then blank lines then go through all the map to get its size
// Also checks if there is a blank line inside the map definition
// Returns FALSE on error
static	t_bool	init_map_size(t_map *s_map, int fd)
{
	char	*line;

	line = free_strtrim(get_next_line(fd), "\n");
	while (line && ft_str_is_wspace(line))
	{
		free(line);
		line = free_strtrim(get_next_line(fd), "\n");
	}
	if (!line)
		return (FALSE);
	s_map->xsize = 0;
	s_map->ysize = 0;
	while (line && !ft_str_is_wspace(line))
	{
		if (ft_strlen(line) > s_map->xsize)
			s_map->xsize = ft_strlen(line);
		s_map->ysize++;
		free(line);
		line = free_strtrim(get_next_line(fd), "\n");
	}
	if (ft_str_is_wspace(line))
		return (ft_putstr_fd("Blank line inside map\n", 2), FALSE);
	printf("Size of the map (x , y) = (%li , %li)\n", s_map->xsize, s_map->ysize);
	return (TRUE);
}

// Used on the second opening of the map file to skip the textures paths
static void	skip_textures(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		while (line && ft_str_is_wspace(line))
		{
			free(line);
			line = get_next_line(fd);
		}
		count++;
		free(line);
		if (count == 6)
			break;
		line = get_next_line(fd);
	}
}

// Allocates and prepares the string that are going to map_tab accordingly
// --> No trailing spaces \n nor tabs
// Returns NULL on error
static char	*create_map_tab_str(char *line, size_t size)
{
	char	*str;
	char	*trim;

	trim = trim_trail(line);
	if (!trim)
		return (NULL);
	str = malloc((size + 1) * sizeof(char));
	if (!str)
		return (free(trim), NULL);
	size_t	i = 0;
	str[size] = '\0';
	while (i < size)
	{
		// if (i < ft_strlen(trim))
		// {
		// 	if ((trim[i] == ' ' || trim[i] == '\t'))
		// 	{
		// 		if (i > 0 && str[i - 1] != '-')
		// 			str[i] = INSPACE;
		// 		else
		// 			str[i] = OUTSIDE;
		// 	}
		// 	else
		// 		str[i] = trim[i];
		// }
		// else
		// 	str[i] = OUTSIDE;
		str[i] = trim[i];
		i++;
	}
	return (free(trim), str);
}

// Allocates map tab accordingly then reads the map file to fill it up
// Return false on error
static t_bool	fill_map_tab(t_map *s_map, int fd)
{
	char	*line;
	size_t	i;

	s_map->map_tab = malloc((s_map->ysize + 1) * sizeof(char *));
	if (!s_map->map_tab)
		return (FALSE);
	s_map->map_tab[s_map->ysize] = NULL;
	line = get_next_line(fd);
	while (line && ft_str_is_wspace(line))
	{
		free(line);
		line = get_next_line(fd);
	}
	i = 0;
	while (i < s_map->ysize)
	{
		s_map->map_tab[i] = create_map_tab_str(line, s_map->xsize);
		if (!s_map->map_tab[i])
			return (free(line), FALSE);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	return (TRUE);
}

// The reading head corresponding to fd is supposed to be positionned AFTER all
// textures path on the map file
// Reads the file until the end to calculate the size of the map then
// reopens the map file from the beginning to fill up map_tab of s_map
// Returns FALSE on error
static t_bool	init_map_tab(t_map *s_map, char *path, int fd)
{
	if (!init_map_size(s_map, fd))
		return (close(fd), FALSE);
	close(fd);	
	fd = open(path, O_RDONLY); // Comment check si c'est bien un fichier et non un directory ?
	if (fd < 0)	
		return (perror("Open failed"), FALSE);
	skip_textures(fd);
	if (!fill_map_tab(s_map, fd))
		return (close(fd), FALSE);
	return (close(fd), TRUE);
}

// Opens the map file, then init every elements of s_map struct
// Returns false on error
t_bool	init_s_map(t_map *s_map, char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (perror("Open failed"), FALSE);
	if (!init_textures(s_map, fd))	
		return (manage_error("Failed to init textures\n"), close(fd), FALSE);
	if (!init_map_tab(s_map, path, fd))
		return (manage_error("Failed to init map tab\n"), FALSE);
	return (TRUE);
}
