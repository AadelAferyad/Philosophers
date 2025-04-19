/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:05:11 by aaferyad          #+#    #+#             */
/*   Updated: 2025/04/19 13:53:56 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int ac, char **av)
{
	t_table	table_info;

	if (ac != 5 && ac != 6)
		print_error("Invalid number of arguments\n");
	parser(&table_info, av);
	return (0);
}
