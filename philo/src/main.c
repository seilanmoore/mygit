/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smoore-a <smoore-a@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 00:38:52 by smoore-a          #+#    #+#             */
/*   Updated: 2024/11/30 11:12:39 by smoore-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	data = (t_data){0};
	if (check_info(&data, argc, argv))
		return (data.e_code);
	if (init(&data))
		return (cleanup(&data), data.e_code);
	i = -1;
	while (++i < data.info.n_philo)
		pthread_join(data.philo[i].thread, NULL);
	cleanup(&data);
	return (EXIT_SUCCESS);
}
