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

#define MALLOC_PROG
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
		s->ptr = ptr + sizeof(struct s_shield);
		s->size = 0;
		s->next = NULL;
		s->left = NULL;
		s->free = FALSE;
	}
	return (s);
}
