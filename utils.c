/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:52:03 by aaferyad          #+#    #+#             */
/*   Updated: 2025/08/09 15:55:19 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	destroy_mutex(t_sim *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
		pthread_detach(data->philos[i].thread);
		i++;
	}
	pthread_mutex_destroy(&data->end_simulation_mutex);
	pthread_mutex_destroy(&data->print);
	return (0);
}

int	full_cleanup(t_sim *data)
{
	destroy_mutex(data);
	free(data->philos);
	free(data->forks);
	return (0);
}

int	print_error_return(char *error, int return_code)
{
	printf(RED"%s\n"RESET, error);
	return (return_code);
}

void	cleanup(t_sim *data)
{
	free(data->philos);
	free(data->forks);
}
