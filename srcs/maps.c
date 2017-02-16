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

#include "mallocstandard.h"

t_map	*getallmaps(void)
{
	static t_map	*map;

	if (map == NULL)
	{
		map = (t_map*)ft_mmap(0, sizeof(t_map), PROT_READ | PROT_WRITE, 0);
		if (map == (void*)-1)
			return (NULL);
		map->data = NULL;
		map->next = NULL;
		map->left = NULL;
		map->zone = ZONE_TINY;
		map->first = TRUE;
	}
	return (map);
}

t_map	*newmap(t_map *map, t_zone zone, int large_size)
{
	t_map	*newm;
	int		size;

	if (zone >= ZONE_LARGE)
		size = large_size;
	else
		size = (zone == ZONE_TINY ? TINY : SMALL);
	newm = (t_map*)ft_mmap(0, sizeof(t_map) + (size * 2), PROT_READ | PROT_WRITE, 0);
	if (newm == (void*)-1)
		return (NULL);
	newm->next = NULL;
	newm->left = map;
	if (map != NULL)
		map->next = newm;
	newm->zone = zone;
	newm->first = FALSE;
	newm->data = add_clean_shield(newm + 1);
	if (newm->data == NULL)
	{
		printf("data == NULL\n");
		return (NULL);
	}
	return (newm);
}

BOOLEAN	haszone(t_zone zone)
{
	t_map *map;

	map = getallmaps();
	while (map)
	{
		if (map->first == FALSE && map->zone == zone)
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
