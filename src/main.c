/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlebon <tlebon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 16:02:37 by tlebon            #+#    #+#             */
/*   Updated: 2025/02/11 21:14:50 by tlebon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Returns true if the file pointed to by path has the matching extension
static t_bool	check_extension(char *path, char *extension)
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

// Initialize the global struct that contains all the necessary structs
// Returns false on error
t_bool	init_global(t_global *s_global, char *path)
{
	s_global->s_map = malloc(sizeof(t_map));
	if (!s_global->s_map)
		return (FALSE);
	s_global->s_mlx = malloc(sizeof(t_mlx));
	if (!s_global->s_mlx)
		return (free(s_global->s_map), FALSE);
	if (init_s_map(s_global->s_map, path) == FALSE)
		return (FALSE);
	ft_printf("Map struct created with success !\n");
	ft_print_str_tab(s_global->s_map->map_tab);
	if (init_s_mlx(s_global->s_mlx) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	main (int ac, char **av)
{
	t_global	s_global;

	if (ac != 2)
		return (ft_printf("Usage : ./cub3D valid_map_path\nThanks\n"), 1);
	if (check_extension(av[1], ".cub") == FALSE)
		return (ft_putstr_fd("You need to select a .cub file\n", 2), 2);
	if (!init_global(&s_global, av[1]))
		return (3);
	game_loop(&s_global);
	return (0);
}

// int	main(void)
// {
// 	// char	*s = "	  1111111111111  1111 11  1			   \n";
// 	char	*s = ft_strdup(" 11				\n   ");
// 	char	*test = trim_trail(s);
// 	printf("%s", test);
// 	return (0);
// }

