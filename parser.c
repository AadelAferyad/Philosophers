/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:33:49 by aaferyad          #+#    #+#             */
/*   Updated: 2025/07/30 18:07:32 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
 * ./a.out 5 200 400 100 (5)
 * */

static int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ascii_to_int(char *str)
{
	int	i;
	long	n;
	int	len;

	i = 0;
	n = 0;
	len = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-')
		print_error("Invalid argument digits should be positive\n");
	if (str[i] == '+')
		i++;
	if (!(str[i] >= '0' && str[i] <= '9'))
		print_error("Invalid argument it should be a digit\n");
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + str[i] - '0';
		len++;
		i++;
	}
	if (len > 10 || n > INT_MAX)
		print_error("Invalid argument the value is to big then INT_MAX\n");
	return ((int) n);
}

void	parser(simulation *data, char **av)
{
	int	*tmp;

	data->n_philo = (unsigned int) ascii_to_int(av[1]);
	data->t_die = (unsigned int) ascii_to_int(av[2]);
	data->t_eat = (unsigned int) ascii_to_int(av[3]);
	data->t_sleep = (unsigned int) ascii_to_int(av[4]);
	tmp = get_time_to_sleep();
	*tmp= data->t_sleep;
	tmp = get_time_to_eat();
	*tmp = data->t_eat;
	if (av[5])
		data->n_simulation = ascii_to_int(av[5]);
}
