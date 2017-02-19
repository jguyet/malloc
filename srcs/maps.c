/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 01:12:11 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/16 01:12:12 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MALLOC_PROG
#include "mallocstandard.h"

t_map	*getallmaps(void)
{
	static t_map	*map;
	void			*ptr;

	if (map == NULL)
	{
		ptr = (void*)ft_mmap(0, sizeof(t_map), PROT_READ | PROT_WRITE, 0);
		if (ptr == (void*)-1)
			return (NULL);
		map = (t_map*)ptr;
		map->data = NULL;
		map->next = NULL;
		map->left = NULL;
		map->zone = ZONE_TINY;
		map->first = TRUE;
		map->ptr = ptr;
		map->size_place = 0;
	}
	return (map);
}

t_map	*newmap(t_map *map, t_zone zone, int large_size)
{
	t_map	*newm;
	int		size;
	void	*ptr;

	if (zone >= ZONE_LARGE)
		size = sizeof(t_shield) + large_size;
	else
		size = (sizeof(t_shield) * ZONE_MAX_SIZE) + (zone == ZONE_TINY ? TINY : SMALL);
	ptr = (void*)ft_mmap(0, sizeof(t_map) + size, PROT_READ | PROT_WRITE, 0);
	if (ptr == (void*)-1)
		return (NULL);
	newm = (t_map*)ptr;
	newm->next = NULL;
	newm->left = map;
	if (map != NULL)
		map->next = newm;
	newm->zone = zone;
	newm->first = FALSE;
	create_shields(ptr + sizeof(t_map), zone, large_size);
	newm->ptr = ptr;
	newm->data = get_shield_id(newm, 0);
	newm->size_place = 0;
	if (newm->data == NULL)
	{
		printf("newm->data == NULL\n");
		return (NULL);
	}
	return (newm);
}

t_map	*add_new_map(t_zone zone, int large_size)
{
	t_map	*newm;
	t_map	*map;

	if ((map = getallmaps()) == NULL)
		return (NULL);
	while (map->next)
		map = map->next;
	if (!(newm = newmap(map, zone, large_size)))
		return (NULL);
	newm->data->size = large_size;
	return (newm);
}

size_t	get_used_size(t_map *map)
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

size_t	get_free_size(t_map *map)
{
	size_t used;

	used = get_used_size(map);
	if (map->zone == ZONE_TINY)
		return (TINY - used);
	if (map->zone == ZONE_SMALL)
		return (SMALL - used);
	return (0);
}

size_t	get_free_number_places(t_map *map)
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

void	reatribute_size(t_map *map)
{
	t_shield	*s;
	int			size;

	s = map->data;
	size = get_free_size(map) / get_free_number_places(map);
	map->size_place = size;
	while (s)
	{
		if (s->free == TRUE)
			s->size = size;
		s = get_shield_id(map, s->id + 1);
	}
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

BOOLEAN	haszone(t_zone zone)
{
	t_map *map;

	map = getallmaps();
	while (map)
	{
		if (map->first == FALSE && map->first == FALSE && map->zone == zone)
			return (TRUE);
		map = map->next;
	}
	return (FALSE);
}

t_map	*getmap_by_zone(t_zone zone)
{
	t_map *map;

	map = getallmaps();
	while (map)
	{
		if (map->first == FALSE && map->zone == zone)
			return (map);
		map = map->next;
	}
	return (NULL);
}
