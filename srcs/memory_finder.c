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

#include "mallocstandard.h"

t_shield				*get_shield(size_t size)
{
	t_shield	*potential_shield;
	t_map		*map;
	t_zone		zone;

	potential_shield = NULL;
	map = NULL;
	zone = get_zone_type_by_size(size);
	if (!haszone(zone))
	{
		if (!(map = newmap(getallmaps(), zone, size)))
		{
			printf("map == NULL\n");
			return (NULL);
		}
		potential_shield = map->data;
		potential_shield->size = size;
	}
	else
		map = getmap_by_zone(zone);
	if (potential_shield == NULL && zone < ZONE_LARGE)
	{
		potential_shield = check_zone(size, map->data, zone);
		printf("HAHAHAHHAHA\n");
	}
	//else
		/////generation d'une mmap unique pour le shield (UNIQUEMENT LARGE ZONES)
	if (potential_shield == NULL)//cree une nouvelle map
	{
		printf("potential_shield == NULL\n");
		return (NULL);
	}
	printf("in zone : %d, size : %zu, ptr : %p\n", (zone == ZONE_TINY ? TINY : SMALL), potential_shield->size, potential_shield->ptr);
	return (potential_shield);
}

/*
** check zone sizes with size_t size and return ZONE_TYPE
** equivalente
*/
t_zone					get_zone_type_by_size(size_t size)
{
	size_t	page_size;

	page_size = getpagesize();

	if (page_size < size)
		return (ZONE_LARGE);
	if ((size + sizeof(struct s_shield)) < (TINY / ZONE_MAX_SIZE))
		return (ZONE_TINY);
	if ((size + sizeof(struct s_shield)) < (SMALL / ZONE_MAX_SIZE))
		return (ZONE_SMALL);
	return (ZONE_LARGE);
}

t_shield				*check_zone(size_t size, t_shield *s, t_zone zone)
{
	t_shield	*check;
	int			alloc;
	size_t		octet;

	check = s;
	alloc = 0;
	octet = 0;
	//cherche une bonne zone deja free
	while (check && (check->free == FALSE || check->size < size))
	{
		alloc++;
		octet += check->size;
		check = check->next;
		if (s->next)
			s = s->next;
	}
	if (check == NULL)
		printf("check == null\n");
	if (check == NULL && alloc < ZONE_MAX_SIZE && s\
		&& (octet + size) < (zone == ZONE_TINY ? TINY : SMALL))
		check = add_clean_shield(((char*)s + sizeof(struct s_shield) + s->size));
	else if (check == NULL)
		return (NULL);
	printf("check != null\n");
	check->size = size;
	check->left = s;
	s->next = check;
	printf("check_zone zone : %d, size : %zu, alloc : %d, octet_used : %zu\n", (zone == ZONE_TINY ? TINY : SMALL), check->size, alloc, octet);
	return (check);
}

void					place_shield_to_end(t_shield *s, size_t size)
{
	t_shield	*news;

	news = (t_shield*)((char*)s + size);
	news->size = size - sizeof(struct s_shield);
	news->free = FALSE;
	news->left = s;
	news->next = NULL;
	news->ptr = news + 1;
	if (news->left != NULL)
		news->left->next = news;
	if (news->next != NULL)
		news->next->left = news;
}
