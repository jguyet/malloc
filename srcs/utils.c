/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 11:22:46 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/20 11:22:47 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MALLOC_PROG
#include "mallocstandard.h"

size_t		get_used_size(t_map *map)
{
	t_shield	*s;
	size_t		size;

	size = 0;
	s = map->data;
	while (s)
	{
		if (s->free == FALSE)
			size += s->size;
		s = get_shield_id(map, s->id + 1);
	}
	return (size);
}

size_t		get_free_size(t_map *map)
{
	size_t	used;

	used = get_used_size(map);
	if (map->zone == ZONE_TINY)
		return (TINY - used);
	if (map->zone == ZONE_SMALL)
		return (SMALL - used);
	return (0);
}

size_t		get_free_number_places(t_map *map)
{
	t_shield	*s;
	size_t		size;

	size = 0;
	s = map->data;
	while (s)
	{
		if (s->free == TRUE)
			size++;
		s = get_shield_id(map, s->id + 1);
	}
	return (size);
}

t_shield	*get_free_shield(t_map *map, size_t size)
{
	t_shield	*s;

	s = map->data;
	while (s)
	{
		if (s->free == TRUE && s->size >= size)
		{
			return (s);
		}
		s = get_shield_id(map, s->id + 1);
	}
	return (NULL);
}

size_t		get_size_place(t_map *map)
{
	if (map->zone == ZONE_TINY)
		return (TINY / ZONE_MAX_SIZE);
	if (map->zone == ZONE_TINY)
		return (SMALL / ZONE_MAX_SIZE);
	return (0);
}
