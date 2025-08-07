/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:05:11 by aaferyad          #+#    #+#             */
/*   Updated: 2025/08/07 14:59:13 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int ac, char **av)
{
	t_sim	data;

	if (ac != 5 && ac != 6)
		print_error_exit("Invalid number of arguments");
	if (parser(&data, av))
		return (1);
	if (init(&data))
		return (1);
	dinning(data);
	return (0);
}
