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
	while (i < table->nb_philo)
		table->philos[i].id = i++;
}
