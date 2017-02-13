/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 17:07:37 by jguyet            #+#    #+#             */
/*   Updated: 2016/08/20 17:09:50 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mallocstandard.h>

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
** Alloue une zone memoir de la taille size et
** retourne le pointer de debut.
*/
void	*malloc(size_t size)
{
	(void)size;
	return (NULL);
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
	return (ft_mmap(0, size, PROT_READ | PROT_WRITE, 0));
}