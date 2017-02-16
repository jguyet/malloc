/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/16 00:53:16 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/16 00:53:17 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mallocstandard.h"

/*
** Aloue une map du size size_map et retourne
** un pointer frais sur le premier t_sheald
*/
t_shield	*malloc_map(size_t size_map)
{
	t_shield	*s;

	s = NULL;
	if (s == NULL)
	{
		s = (t_shield*)ft_mmap(0, size_map, PROT_READ | PROT_WRITE, 0);
		if (s == (void*)-1)
			return (NULL);
		s->size = 0;
		s->ptr = NULL;
		s->next = NULL;
		s->left = NULL;
		s->free = FALSE;
	}
	return (s);
}

t_shield	*add_clean_shield(void *ptr)//((char*)map + sizeof(struct s_map))
{
	t_shield	*s;

	s = NULL;
	if (s == NULL)
	{
		s = (t_shield*)ptr;
		if (s == (void*)-1)
			return (NULL);
		s->ptr = s + 1;
		s->size = 0;
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
t_shield	*malloc_tiny(void)
{
	t_shield	*s;

	s = malloc_map(TINY);
	return (s);
}

/*
** Aloue une map de la taille small
** et renvoi le pointer de depart sois t_sheald start.
*/
t_shield	*malloc_small(void)
{
	t_shield	*s;

	s = malloc_map(SMALL);
	return (s);
}

/*
** Aloue une map de la taille size avec les deux sheald
** et renvoi le pointer de depart sois t_sheald start.
*/
t_shield	*malloc_large(size_t size)
{
	t_shield	*s;

	s = malloc_map((sizeof(struct s_shield) * 2) + size);
	return (s);
}

/*
** suivant la t_zone zone un choix d'allocation de map et
** interprerter
*/
t_shield	*switch_malloc(size_t size, t_zone zone)
{
	if (zone == ZONE_TINY)
		return (malloc_tiny());
	if (zone == ZONE_SMALL)
		return (malloc_small());
	return (malloc_large(size));
}
