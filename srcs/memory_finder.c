/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 19:55:07 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/15 19:55:08 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MALLOC_PROG
#include "mallocstandard.h"

t_shield				*get_shield_new_map(t_zone zone, size_t size)
{
	t_map		*map;

	map = NULL;
	if (!(map = add_new_map(zone, size)))
	{
		printf("map == NULL\n");
		return (NULL);
	}
	map->data->ptr = get_ptr_id(map, 0);
	map->data->size = size;
	map->size_place = zone == ZONE_LARGE ? 0 : (map->zone == ZONE_TINY ? TINY : SMALL);
	map->size_place -= zone == ZONE_LARGE ? 0 : (map->zone == ZONE_TINY ? 1024 : 4096);
	return (map->data);
}

t_shield				*check_free_place(t_zone zone, size_t size)
{
	t_map		*map;
	t_shield	*s;

	map = getallmaps();
	while (map)
	{

		if (map->first == FALSE && map->zone == zone\
			&& map->size_place >= size)
		{
			s = get_free_shield(map, size);
			if (s != NULL)
			{
				if (s->ptr == NULL)
					s->ptr = get_ptr_id(map, s->id);
				map->size_place -= map->zone == ZONE_LARGE ? 0 : (map->zone == ZONE_TINY ? 1024 : 4096);
				return (s);
			}
		}
		map = map->next;
	}
	return (get_shield_new_map(zone, size));
}

t_shield				*get_shield(size_t size)
{
	t_shield	*potential_shield;
	t_zone		zone;

	potential_shield = NULL;
	zone = get_zone_type_by_size(size);
	if (!haszone(zone))
	{
		potential_shield = get_shield_new_map(zone, size);
	}
	else
	{
		potential_shield = check_free_place(zone, size);
	}
	if (potential_shield != NULL)
	{
		potential_shield->size = size;
	}
	//else
		/////generation d'une mmap unique pour le shield (UNIQUEMENT LARGE ZONES)
	if (potential_shield == NULL)
		return (NULL);
	return (potential_shield);
}

/*
** check zone sizes with size_t size and return ZONE_TYPE
** equivalente
*/
t_zone					get_zone_type_by_size(size_t size)
{
	if (size <= (size_t)(TINY / ZONE_MAX_SIZE))
		return (ZONE_TINY);
	if (size <= (size_t)(SMALL / ZONE_MAX_SIZE))
		return (ZONE_SMALL);
	return (ZONE_LARGE);
}

void					find_and_free_map(void)
{
	t_map	*map;
	int		size;
	t_map	*tmp;

	map = getallmaps();
	while (map)
	{
		if (map->first == FALSE && get_used_size(map) == 0)
		{
			if (map->left)
				map->left->next = (map->next ? map->next : NULL);
			if (map->next)
				map->next->left = (map->left ? map->left : NULL);
			if (map->zone >= ZONE_LARGE)
				size = sizeof(t_shield) + map->data->size;
			else
				size = (sizeof(t_shield) * ZONE_MAX_SIZE) + (map->zone == ZONE_TINY ? TINY : SMALL);
			tmp = map->next;
			show_alloc_mem();
			munmap(map->ptr, sizeof(t_map) + size);
			//printf("LA4 %p\n", map);
			//printf("return (%d) munmap;\n", munmap(map->ptr, sizeof(t_map) + size));
			//printf("LA5 %p\n", map);
			map = tmp;
			continue ;
		}
		map = map->next;
	}
}
