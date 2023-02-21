/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasalama < sasalama@student.42madrid.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:45:31 by sasalama          #+#    #+#             */
/*   Updated: 2023/02/21 09:43:44 by valarcon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "./includes/camera.h"
#include "./includes/color.h"
#include "./includes/file_reader.h"
#include "./includes/geometry.h"
#include "./includes/raytracer.h"
#include "./includes/vector.h"
#include "./includes/ft_process.h"

// Creación ventana

typedef struct s_s
{
	void	*mlx;
	void	*mlx_win;
}				t_s;

int	ft_exit_hook(t_s *window)
{
	mlx_destroy_window(window->mlx, window->mlx_win);
	exit(-1);
}

int	key_hook(int keycode, t_s *window)
{
	if (keycode == 53)
		ft_exit_hook(window);
	return (0);
}

//

int	main(int argc, char *argv[])
{
	char	*s;
	char	**lines;
	int		x;
	t_s		window;
	
	t_conf conf;

	if (argc != 2)
	{
		perror("Error in number of arguments");
		return (1);
	}
	s = ft_data(argv);
	if (!s)
	{
		perror("Error in open the file");
		return (1);
	}
	lines = ft_split(s, '\n');
	x = 0;
	while (lines[x])
	{
		printf("%s\n", lines[x]);
		x++;
	}
	conf = ft_process(lines);
	printf("%i\n", conf.flag.error);
	if (conf.flag.error != 0)
	{
		printf("ERROR");
		return (0);
	}
	window.mlx = mlx_init();
	window.mlx_win = mlx_new_window(window.mlx, 1920, 1080, "MiniRT");
	mlx_pixel_put(window.mlx, window.mlx_win, 200, 200, 0xfafad2);
	mlx_key_hook(window.mlx_win, key_hook, &window);
	mlx_hook(window.mlx_win, 17, 1L << 17, ft_exit_hook, &window);
	mlx_loop(window.mlx);
	free(window.mlx);
	free(window.mlx_win);
	//
	return (0);
}
