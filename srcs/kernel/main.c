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

#include <mallocStandard.h>

void			free(void *ptr)
{
	(void)ptr;
}

void			*malloc(size_t size)
{
	(void)size;
	return (NULL);
}

void			*realloc(void *ptr, size_t size)
{
	(void)ptr;
	(void)size;
	return (NULL);
}
