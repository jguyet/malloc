/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 18:20:44 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/20 18:20:46 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MALLOC_PROG
#include "mallocstandard.h"

static void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*tmp1;
	const char	*tmp2;
	size_t		i;

	tmp1 = dst;
	tmp2 = src;
	i = 0;
	while (i < n)
	{
		*tmp1++ = *tmp2++;
		i++;
	}
	return (dst);
}

static t_shield		*get_shield_r(t_map *map, void *ptr, size_t size)
{
	t_shield	*s;

	s = map->data;
	while (s)
	{
		if (s->ptr == ptr)
			break ;
		s = get_shield_id(map, s->id + 1);
	}
	if (s != NULL && size <= get_size_place(map))
	{
		s->size = size;
		return (s->ptr);
	}
	return (s);
}

void				*realloc_memory(void *ptr, size_t size)
{
	t_map		*map;
	t_shield	*s;

	map = getallmaps();
	while (map)
	{
		if (map->first || ptr < get_start_ptr_zone(map)
			|| ptr > get_end_ptr_zone(get_start_ptr_zone(map), map))
		{
			map = map->next;
			continue ;
		}
		s = get_shield_r(map, ptr, size);
		if (s == NULL)
			return (NULL);
		if (!(ptr = malloc(size)))
			return (NULL);
		ft_memcpy(ptr, s->ptr, s->size);
		return (ptr);
	}
	return (NULL);
}
