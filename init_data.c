/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:51:28 by aaferyad          #+#    #+#             */
/*   Updated: 2025/04/20 19:52:53 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init(t_table *table)
{
	int	i;

	i = 0;
	table->philos = allocation(table->nb_philo * sizeof(t_philo));
	while (++i <= table->nb_philo)
		table->philos[i - 1].id = i;
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_create(&table->philos[i].philo, NULL, philo_cycle, NULL);
		if (table->philos[i].philo != 0)
		{
			cleanup(table);
			print_error("Could't create a thread\n");
		}
		i++;
	}
}
