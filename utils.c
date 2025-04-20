/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaferyad <aaferyad@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 13:52:03 by aaferyad          #+#    #+#             */
/*   Updated: 2025/04/20 13:54:49 by aaferyad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	*allocation(unsigned int bytes)
{
	void	*ptr;

	ptr = malloc(bytes);
	if (!ptr)
		print_error("Malloc failed\n");
	return (ptr);
}
