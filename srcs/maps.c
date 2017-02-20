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

t_map		*getallmaps(void)
{
	static t_malloc	*m;
	void			*ptr;

	if (m == NULL)
	{
		ptr = (void*)ft_mmap(0, sizeof(t_malloc), PROT_READ | PROT_WRITE, 0);
		if (ptr == (void*)-1)
			return (NULL);
		m = (t_malloc*)ptr;
		m->data = NULL;
		m->next = NULL;
		m->left = NULL;
		m->zone = ZONE_TINY;
		m->first = TRUE;
		m->ptr = ptr;
		m->size_place = 0;
		m->older_alloc_size = 0;
		m->retry = 0;
	}
	return ((t_map*)m);
}

t_map		*newmap(t_map *map, t_zone zone, int large_size)
{
	t_map	*newm;
	int		size;
	void	*ptr;

	if (zone >= ZONE_LARGE)
		size = sizeof(t_shield) + large_size;
	else
		size = (sizeof(t_shield) * ZONE_MAX_SIZE) + \
	(zone == ZONE_TINY ? TINY : SMALL);
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
	return (newm->data == NULL ? NULL : newm);
}

t_map		*add_new_map(t_zone zone, int large_size)
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

BOOLEAN		haszone(t_zone zone)
{
	t_map	*map;

	map = getallmaps();
	while (map)
	{
		if (map->first == FALSE && map->first == FALSE && map->zone == zone)
			return (TRUE);
		map = map->next;
	}
	return (FALSE);
}

t_map		*getmap_by_zone(t_zone zone)
{
	t_map	*map;

	map = getallmaps();
	while (map)
	{
		if (map->first == FALSE && map->zone == zone)
			return (map);
		map = map->next;
	}
	return (NULL);
}
