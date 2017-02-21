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
	getallmaps();
	pthread_mutex_lock(&g_lock);
	if (!(result = get_shield(size)))
		return (NULL);
	result->free = FALSE;
	pthread_mutex_unlock(&g_lock);
	return (result->ptr);
}

void	free(void *ptr)
{
	if (ptr == NULL)
		return ;
	getallmaps();
	pthread_mutex_lock(&g_lock);
	free_ptr(ptr);
	pthread_mutex_unlock(&g_lock);
}

void	*realloc(void *ptr, size_t size)
{
	void *nptr;

	if (ptr == NULL)
		return (NULL);
	getallmaps();
	pthread_mutex_lock(&g_lock);
	nptr = realloc_memory(ptr, size);
	pthread_mutex_unlock(&g_lock);
	return (nptr);
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

void	show_hexa_mem(void)
{
	if (get_count_zone(ZONE_TINY) > 0)
	{
		ft_putstr("<----------------------------HEXA-TINY");
		ft_putstr("---------------------------->\n");
		print_hexa_zone(ZONE_TINY);
	}
	if (get_count_zone(ZONE_SMALL) > 0)
	{
		ft_putstr("<----------------------------HEXA-SMALL");
		ft_putstr("--------------------------->\n");
		print_hexa_zone(ZONE_SMALL);
	}
	if (get_count_zone(ZONE_LARGE) > 0)
	{
		ft_putstr("<----------------------------HEXA-LARGE");
		ft_putstr("--------------------------->\n");
		print_hexa_zone(ZONE_LARGE);
	}
}
