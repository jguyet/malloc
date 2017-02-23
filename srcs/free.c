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

void		*get_start_ptr_zone(t_map *map)
{
	void	*start_p;

	start_p = map->ptr + sizeof(t_map);
	if (map->zone == ZONE_LARGE)
		start_p += sizeof(t_shield);
	else
		start_p += sizeof(t_shield) * ZONE_MAX_SIZE;
	return (start_p);
}

void		*get_end_ptr_zone(void *start_p, t_map *map)
{
	void	*end_p;

	if (map->zone == ZONE_LARGE)
		end_p = start_p + map->data->size;
	else
		end_p = start_p + (map->zone == ZONE_TINY ? TINY : SMALL);
	return (end_p);
}

BOOLEAN		free_shield(void *ptr, t_map *map)
{
	t_shield	*s;
	void		*start_p;

	s = map->data;
	start_p = get_start_ptr_zone(map);
	if (ptr < start_p || ptr > get_end_ptr_zone(start_p, map))
		return (FALSE);
	while (s)
	{
		if (s->free == FALSE && s->ptr == ptr)
		{
			s->free = TRUE;
			map->size_place += get_size_place(map->zone);
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
		map->left->next = map->next ? map->next : NULL;
	if (map->next)
		map->next->left = map->left ? map->left : NULL;
	if (map->zone >= ZONE_LARGE)
		size = sizeof(t_shield) + map->data->size;
	else
		size = (sizeof(t_shield) * ZONE_MAX_SIZE) \
		+ (map->zone == ZONE_TINY ? TINY : SMALL);
	munmap(map->ptr, sizeof(t_map) + size);
}

void		free_ptr(void *ptr, BOOLEAN print)
{
	t_map *map;

	map = getallmaps();
	(void)print;
	while (map)
	{
		if (map->first == FALSE && free_shield(ptr, map))
		{
			if (map->zone == ZONE_LARGE && get_used_size(map) == 0)
				free_map(map);
			else if (map->zone != ZONE_LARGE &&
				get_count_zone(map->zone) > 1 && get_used_size(map) == 0)
				free_map(map);
			return ;
		}
		map = map->next;
	}
}
