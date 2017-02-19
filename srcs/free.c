/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 13:29:43 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/19 13:29:45 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MALLOC_PROG
#include "mallocstandard.h"

BOOLEAN		free_shield(void *ptr, t_map *map)
{
	t_shield	*s;
	void		*start_p;
	void		*end_p;

	s = map->data;
	start_p = map->ptr + sizeof(t_map) + (map->zone == ZONE_LARGE ? sizeof(t_shield) : (sizeof(t_shield) * ZONE_MAX_SIZE));
	end_p = (map->zone == ZONE_LARGE ? start_p + map->data->size : start_p + (map->zone == ZONE_TINY ? TINY : SMALL));

	if (ptr < start_p || ptr > end_p)
		return (FALSE);
	while (s)
	{
		if (s->free == FALSE && s->ptr == ptr)
		{
			s->free = TRUE;
			map->size_place += map->zone == ZONE_LARGE ? 0 : (map->zone == ZONE_TINY ? 1024 : 4096);
			return (TRUE);
		}
		s = get_shield_id(map, s->id + 1);
	}
	return (FALSE);
}

void		free_map(t_map *map)
{
	size_t	size;

	if (map->left)
		map->left->next = (map->next ? map->next : NULL);
	if (map->next)
		map->next->left = (map->left ? map->left : NULL);
	if (map->zone >= ZONE_LARGE)
		size = sizeof(t_shield) + map->data->size;
	else
		size = (sizeof(t_shield) * ZONE_MAX_SIZE) + (map->zone == ZONE_TINY ? TINY : SMALL);
	munmap(map->ptr, sizeof(t_map) + size);
}

void		free_ptr(void *ptr)
{
	t_map *map;

	map = getallmaps();
	while (map)
	{
		if (map->first == FALSE && free_shield(ptr, map))
		{
			if (map->zone == ZONE_LARGE && get_used_size(map) == 0)
				free_map(map);
			return ;
		}
		map = map->next;
	}
}
