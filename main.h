/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:49:08 by aaferyad          #+#    #+#             */
/*   Updated: 2025/04/22 14:25:04 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

typedef struct	philo_s
{
	int	id;
	pthread_t	philo;
} t_philo;

typedef struct	s_table
{
	unsigned int	nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	int	n_diner;
	t_philo	*philos;
}	t_table;

void	parser(t_table *table_info, char **av);
void	print_error(char *msg);
void	*allocation(unsigned int bytes);
void	cleanup(t_table *table);

#endif
