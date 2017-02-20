/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 17:07:37 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/15 19:41:55 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MALLOC_PROG
#include "mallocstandard.h"

void	*malloc(size_t size)
{
	t_shield	*result;

	if (size < 1)
		return (NULL);
	if (!(result = get_shield(size)))
		return (NULL);
	result->free = FALSE;
	return (result->ptr);
}

void	free(void *ptr)
{
	if (ptr == NULL)
		return ;
	free_ptr(ptr);
}

void	*realloc(void *ptr, size_t size)
{
	if (ptr == NULL)
		return (NULL);
	return (realloc_memory(ptr, size));
}

void	show_alloc_mem(void)
{
	size_t	total_size;

	total_size = 0;
	total_size += print_tiny();
	total_size += print_small();
	total_size += print_large();
	ft_putstr("Total : ");
	ft_putnbr(total_size);
	ft_putstr(" octets\n");
}
