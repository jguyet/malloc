/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shield.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 23:40:38 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/17 23:40:40 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MALLOC_PROG
#include "mallocstandard.h"

void		*get_ptr_id(t_map *map, int id)
{
	t_shield	*s;
	int			i;
	int			octet;

	i = 0;
	octet = 0;
	while (i < id && (s = get_shield_id(map, i++)))
		octet += (map->zone == ZONE_TINY ? 1024 : 4096);
	return (map->ptr + sizeof(t_map) + \
		(sizeof(t_shield) * \
			(map->zone == ZONE_LARGE ? 1 : ZONE_MAX_SIZE)) + octet);
}

t_shield	*get_shield_id(t_map *map, int id)
{
	if (map->zone == ZONE_LARGE && id > 0)
		return (NULL);
	if (id >= ZONE_MAX_SIZE)
		return (NULL);
	return ((t_shield*)get_shield_by_id(map->ptr + sizeof(t_map), id));
}

void		*get_shield_by_id(void *ptr, int id)
{
	return (ptr + (sizeof(struct s_shield) * id));
}

void		create_shields(void *ptr, t_zone zone, size_t ssize)
{
	int		i;
	int		size;

	if (zone == ZONE_LARGE)
		size = ssize;
	else if (zone == ZONE_TINY)
		size = TINY / ZONE_MAX_SIZE;
	else
		size = SMALL / ZONE_MAX_SIZE;
	i = 0;
	while (i < (zone == ZONE_LARGE ? 1 : ZONE_MAX_SIZE))
	{
		add_shield(ptr, i, size);
		i++;
	}
}

void		add_shield(void *ptr, int id, int size)
{
	t_shield	*s;

	s = NULL;
	if (s == NULL)
	{
		s = (t_shield*)(ptr + (sizeof(struct s_shield) * id));
		if (s == (void*)-1)
			return ;
		s->id = id;
		s->ptr = NULL;
		s->size = size;
		s->free = TRUE;
	}
}
