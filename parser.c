/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:33:49 by aaferyad          #+#    #+#             */
/*   Updated: 2025/08/07 14:56:10 by aaferyad         ###   ########.fr       */
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

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
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
		return (print_error_exit("Invalid argument digits should be positive", -1));
	if (str[i] == '+')
		i++;
	if (!is_digit(str[i]))
		return (print_error_exit("Invalid argument it should be a digit", -1));
	while (is_digit(str[i]))
	{
		n = (n * 10) + str[i] - '0';
		len++;
		i++;
	}
	if (len > 10 || n > INT_MAX)
		return (print_error_exit("Invalid argument the value is to big then INT_MAX\n", -1));
	return ((int) n);
}

int	parser(t_sim *data, char **av)
{
	int	*tmp;

	data->n_philo = (unsigned int) ascii_to_int(av[1]);
	data->t_die = (unsigned int) ascii_to_int(av[2]);
	data->t_eat = (unsigned int) ascii_to_int(av[3]);
	data->t_sleep = (unsigned int) ascii_to_int(av[4]);
	if (av[5])
		data->n_simulation = ascii_to_int(av[5]);
	else
		data->n_simulation = -1;
	if ((data->n_philo < 1 && data->n_philo <= 200) || data->t_die < 1 || data->t_eat < 1 || data->t_sleep < 1)
		return (1);
	return (0);
}
