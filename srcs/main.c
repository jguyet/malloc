/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 17:07:37 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/15 19:41:55 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mallocstandard.h"

/*
** <b>void			free(void *ptr)</b><br>
** Supprime la zone allouer *ptr.
*/
void	free(void *ptr)
{
	(void)ptr;
}

/*
** <b>void			*malloc(size_t size)</b><br>
** Alloue une zone memoire de la taille size et
** retourne le pointer de debut.
*/
/*void	*malloc(size_t size)
{
	if (size < 1)
		return (NULL);
	t_sheald	left;
	t_sheald	*s;

	s = check_zones(size, &left);

	if (!s)
	{
		t_sheald *news = malloc_small();

		if (news == NULL)
			return (NULL);
		news->next = NULL;
		news->left = &left;
		news->size = (size + sizeof(struct s_sheald)) - sizeof(struct s_sheald);
		news->data = news + 1;
		news->free = 0;
		s = news;
	}
	else if ((size + (sizeof(struct s_sheald) * 2)) < s->size)
	{
		place_sheald_to_end(s, length);
	}
	s->free = 0;
	//recherche de zones possible et ajout de notre debut de chunk et fin.
	return (s->data);
}*/


void	*malloc(size_t size)
{
	if (size < 1)
		return (NULL);
	t_shield	*result;

	if (!(result = get_shield(size)))
		return (NULL);
	result->free = FALSE;
	return (result->ptr);
}

/*
** <b>void			*realloc(void *ptr, size_t size)</b><br>
** Allonge la taille d'une zone et renvoi le nouveau
** pointer de debut.
*/
void	*realloc(void *ptr, size_t size)
{
	(void)ptr;
	(void)size;
	return (NULL);
}

/*
** <b>void			show_alloc_mem(void)</b><br>
** Affiche les zones disponibles TINY, SMALL, LARGE
*/
void	show_alloc_mem()
{
	ft_print("rien");
}

void	*test_malloc(size_t size)
{
	return (malloc(size));
}
