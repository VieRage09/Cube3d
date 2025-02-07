/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:02:37 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/08 00:01:57 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


t_bool	check_extension(char *path, char *extension)
{
	size_t	p_size;
	size_t	e_size;
	char	*ext_comp;

	if (!path || !extension)
		return (FALSE);	
	p_size = ft_strlen(path);
	e_size = ft_strlen(extension);
	ext_comp = ft_substr(path, p_size - e_size, e_size);
	if (ft_strncmp(extension, ext_comp, e_size) == 0)
		return (free(ext_comp), TRUE);
	return (free(ext_comp), FALSE);
}

void	free_all(t_map *s_map)
{
	free(s_map->s_texture.NO);
	free(s_map->s_texture.SO);
	free(s_map->s_texture.EA);
	free(s_map->s_texture.WE);
	free(s_map->s_texture.floor);
	free(s_map->s_texture.ceiling);
}


int	main (int ac, char **av)
{
	// t_mlx	s_mlx;
	t_map	s_map;
	int		fd;
	
	if (ac != 2)
		return (ft_printf("Usage : ./cub3D valid_map_path\nThanks\n"), 1);
	if (check_extension(av[1], ".cub") == FALSE)
		return (ft_putstr_fd("You need to select a .cub file\n", 2), 2);
	fd = open(av[1], O_RDONLY); // Comment check si c'est bien un fichier et non un directory ?
	if (fd < 0)	
		return (perror("Open failed"), 3);
	ft_printf("Map file open with success !\n");
	if (init_s_map(&s_map, fd) == FALSE)
		return (4);
	ft_printf("Map struct created with success !\n");
	// if (init_s_mlx(&s_mlx) == FALSE)
	// 	return (5);
	// mlx_loop(s_mlx.mlx);
	free_all(&s_map);
	if (close(fd) != 0)
		return (5);
	return (0);
}


