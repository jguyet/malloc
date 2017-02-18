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
		//printf("map == NULL\n");
		return (NULL);
	}
	return (map->data);
}

t_shield				*check_free_place(t_zone zone, size_t size)
{
	t_map		*map;
	t_shield	*s;
	t_shield	*result;

	map = getallmaps();
	while (map)
	{

		if (!map->first && map->zone == zone\
			&& get_free_size(map) >= size + sizeof(t_shield))
		{
			s = get_free_shield(map, size);
			if (s != NULL)
			{
	//			printf("return free place\n");//voir si ajout de place libre
				return (s);
			}
			s = map->data;
			while (s->next)
				s = s->next;
	//		printf("add sheald %p on map freesize : %zu\n", s + sizeof(t_shield) + s->size, get_free_size(map));
			result = add_clean_shield(s->ptr + s->size + 1);
			result->left = s;
			s->next = result;
			return (result);
		}
		map = map->next;
	}
	//printf("create new map\n");
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
	//	printf("create new map\n");
		potential_shield = get_shield_new_map(zone, size);
	}
	else
	{
	//	printf("check free places\n");
		//bouclage sur les maps
		//si ont tombe sur la meme map que zone
		//ont regarde s'il y a des places free.
		potential_shield = check_free_place(ZONE_LARGE, size);//replace ZONE_LARGE pars zone
	}
	if (potential_shield != NULL)
	{
		potential_shield->size = size;
	}
	//else
		/////generation d'une mmap unique pour le shield (UNIQUEMENT LARGE ZONES)
	if (potential_shield == NULL)
		return (NULL);
	//printf("return shield s->size : %zu, s->ptr : %p, ptrshield = %p\n", potential_shield->size, potential_shield->ptr, potential_shield);
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
				size = map->data->size;
			else
				size = (map->zone == ZONE_TINY ? TINY : SMALL);
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
