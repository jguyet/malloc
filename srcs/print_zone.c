/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_zone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 14:22:50 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/21 14:22:51 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MALLOC_PROG
#include "mallocstandard.h"

size_t	print_tiny(void)
{
	t_map	*map;
	size_t	total_size;
	BOOLEAN	first;

	map = getallmaps();
	total_size = 0;
	first = TRUE;
	while (map)
	{
		if (map->first == FALSE && map->zone == ZONE_TINY)
		{
			total_size += print_zone("TINY", map, first);
			first = FALSE;
		}
		map = map->next;
	}
	return (total_size);
}

size_t	print_small(void)
{
	t_map	*map;
	size_t	total_size;
	BOOLEAN	first;

	map = getallmaps();
	total_size = 0;
	first = TRUE;
	while (map)
	{
		if (map->first == FALSE && map->zone == ZONE_SMALL)
		{
			total_size += print_zone("SMALL", map, first);
			first = FALSE;
		}
		map = map->next;
	}
	return (total_size);
}

size_t	print_large(void)
{
	t_map	*map;
	size_t	total_size;
	BOOLEAN	first;

	map = getallmaps();
	total_size = 0;
	first = TRUE;
	while (map)
	{
		if (map->first == FALSE && map->zone == ZONE_LARGE)
		{
			total_size += print_zone("LARGE", map, first);
			first = FALSE;
		}
		map = map->next;
	}
	return (total_size);
}
