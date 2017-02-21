/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 19:16:38 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/21 19:16:39 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MALLOC_PROG
#include "mallocstandard.h"

t_shield	*search_ptr_shield(void *ptr, t_map *map)
{
	t_shield	*s;
	void		*start_p;

	s = map->data;
	start_p = get_start_ptr_zone(map);
	if (ptr < start_p || ptr > get_end_ptr_zone(start_p, map))
		return (NULL);
	while (s)
	{
		if (s->ptr == ptr)
			return (s);
		s = get_shield_id(map, s->id + 1);
	}
	return (NULL);
}

t_shield	*search_ptr(void *ptr)
{
	t_map		*map;
	t_shield	*s;

	map = getallmaps();
	while (map)
	{
		if (map->first == FALSE)
		{
			s = search_ptr_shield(ptr, map);
			if (s != NULL)
				return (s);
		}
		map = map->next;
	}
	return (NULL);
}

void		show_hexa_pointer(void *ptr)
{
	t_shield	*s;

	s = search_ptr(ptr);
	if (s == NULL)
		return ;
	print_preshexa_shield(s);
}
