/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:09:45 by aaferyad          #+#    #+#             */
/*   Updated: 2025/08/09 15:40:48 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	print_status(char *status, t_ph *philo)
{
	long	current;
	long	start;

	current = _gettime();
	start = philo->data->simulation_starts;
	printf("%ld %d %s\n", current - start, philo->id, status);
	return (0);
}

int	lock_mutex(pthread_mutex_t *lock)
{
	if (!lock)
		return (1);
	return (pthread_mutex_lock(lock));
}

int	unlock_mutex(pthread_mutex_t *lock)
{
	if (!lock)
		return (1);
	return (pthread_mutex_unlock(lock));
}

int	print_death(t_ph *philo, long current)
{
	long	start;

	start = philo->data->simulation_starts;
	if (lock_mutex(&philo->data->print) != 0)
		return (1);
	printf(RED"%ld %d died\n"RESET, current - start, philo->id);
	if (unlock_mutex(&philo->data->print) != 0)
		return (1);
	return (0);
}
