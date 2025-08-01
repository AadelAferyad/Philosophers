/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:49:08 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/30 18:06:36 by aaferyad         ###   ########.fr       */
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
# include <sys/time.h>

# define RED "\033[31m"
# define GREEN "\033[32m"
# define RESET "\033[0m"

# define true 1
# define false 0

typedef struct	philo_forks
{
	int	fork_id;
	pthread_mutex_t	fork;
} forks;

typedef struct	philosopher
{
	int	id;
	pthread_t	thread;
	int	meal_count;
	forks	*main_fork;
	forks	*next_fork;
} ph;

typedef struct	parsed_data
{
	ph	*philo;
	forks	*fork;
	unsigned int	n_philo;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	int	n_simulation;
} simulation;


void	init(simulation *data);
void	parser(simulation *info, char **av);
void	print_error(char *msg);
void	*allocation(unsigned int bytes);
void	cleanup(simulation *data);
int	*is_simulation_start(void);
int	*get_time_to_sleep(void);
int	*get_time_to_eat(void);

#endif
