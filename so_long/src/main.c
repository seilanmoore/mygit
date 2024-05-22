/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:52:25 by smoore-a          #+#    #+#             */
/*   Updated: 2024/05/22 13:13:02 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	t_data	data;

	data = (t_data){NULL};
	parse_file(&data, argc, argv);
	check_map(&data);
	init_window(&data);
	return (SUCCESS);
}
