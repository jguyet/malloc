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

t_sheald				*malloc_map(size_t size_map)
{
	t_sheald	*s;

	s = NULL;
	if (s == NULL)
	{
		s = (t_sheald*)ft_mmap(0, size_map, PROT_READ | PROT_WRITE, 0);
		
		if (s == (void*)-1)
			return (NULL);
		s->size = 0;
		s->data = NULL;
		s->next = NULL;
		s->left = NULL;
		s->free = FALSE;
	}
	return (s);
}

/*
** Aloue une map de la taille tiny
** et renvoi le pointer de depart sois t_sheald start.
*/
t_sheald				*malloc_tiny()
{
	t_sheald	*s;

	s = malloc_map(TINY);
	return (s);
}

/*
** Aloue une map de la taille small
** et renvoi le pointer de depart sois t_sheald start.
*/
t_sheald				*malloc_small()
{
	t_sheald	*s;

	s = malloc_map(SMALL);
	return (s);
}

/*
** Aloue une map de la taille size avec les deux sheald
** et renvoi le pointer de depart sois t_sheald start.
*/
t_sheald				*malloc_large(size_t size)
{
	t_sheald	*s;

	s = malloc_map((SHEALD_SIZEOF * 2) + size);
	return (s);
}

t_zone					get_zone_type_by_size(size_t size)
{
	size_t	page_size;

	page_size = getpagesize();

	if (page_size < size)
		return (ZONE_LARGE);
	if ((size + SHEALD_SIZEOF) < (TINY / ZONE_SIZE))
		return (ZONE_TINY);
	if ((size + SHEALD_SIZEOF) < (SMALL / ZONE_SIZE))
		return (ZONE_SMALL);
	return (ZONE_LARGE);
}

t_sheald				*switch_malloc(size_t size, t_zone zone)
{
	if (zone == ZONE_TINY)
		return (malloc_tiny());
	if (zone == ZONE_SMALL)
		return (malloc_small());
	return (malloc_large(size));
}

t_sheald				*check_zones(size_t size, t_sheald *left)
{
	t_sheald	*s;
	t_zone		zone;

	zone = get_zone_type_by_size(size);
	s = switch_malloc(size, zone);
	//cherche une bonne zone deja free
	while (s && (s->free == FALSE || s->size < size))
	{
		left = s;
		s = s->next;
	}
	return (s);
}

void					place_sheald_to_end(t_sheald *s, size_t size)
{
	t_sheald	*news;

	news = (t_sheald*)((char*)s + size);
	news->size = size - SHEALD_SIZEOF;
	news->free = FALSE;
	news->left = s;
	news->next = NULL;
	news->data = news + 1;
	if (news->left != NULL)
		news->left->next = news;
	if (news->next != NULL)
		news->next->left = news;
}
