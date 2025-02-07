/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:10:28 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/08 00:13:20 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

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

static char		*free_strtrim(char *str, char *charset)
{
	char	*trim;

	trim = ft_strtrim(str, charset);
	free(str);
	return (trim);
}

static	t_bool	init_map_size(t_map *s_map, int fd) // belec secu si line est NULL pcq eof
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
	s_map->map_tab = NULL;
	printf("Size of the map (x , y) = (%li , %li)\n", s_map->xsize, s_map->ysize);
	return (TRUE);
}

static t_bool	init_map_tab(t_map *s_map, int fd)
{
	if (!init_map_size(s_map, fd))
		return (FALSE);
	fd = open(av[1], O_RDONLY); // Comment check si c'est bien un fichier et non un directory ?
	if (fd < 0)	
		return (perror("Open failed"), 3);
	return (TRUE);
}


t_bool	init_s_map(t_map *s_map, int fd)
{
	char	*line;
	char	*trimed;
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
		trimed = ft_strtrim(line, " \t");
		if (!assign_correct_attribute(trimed, s_map))// leak potentiel
			return (FALSE);
		free(trimed);
		count++;
		free(line);
		if (count == 6)
			break;
		line = get_next_line(fd);
	}
	if (!line)
		return (FALSE);
	printf("Init map tab\n");
	if (!init_map_tab(s_map, fd))
		return (FALSE);
	return (TRUE);
}

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