/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:02:37 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/06 17:41:50 by tlebon           ###   ########.fr       */
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

int	main (int ac, char **av)
{
	int	fd;

	if (ac != 2)
	{
		ft_printf("Usage : ./cub3D valid_map_path\nThanks\n");
		return (1);
	}
	if (check_extension(av[1], ".cub") == FALSE)
	{
		ft_putstr_fd("Wrong file. You need to select a .cub file\n", 2);
		return (2);
	}
	fd = open(av[1], O_RDONLY); // Comment check si c'est bien un fichier et non un directory ?
	if (fd < 0)	
	{
		perror("Open failed");
		return (3);
	}
	return (0);
}
