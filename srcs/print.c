/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 18:35:24 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/20 18:35:26 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MALLOC_PROG
#include "mallocstandard.h"

void	print_pointer(void *ptr)
{
	char	*tmp;

	tmp = NULL;
	ft_putstr("0x");
	if (ptr != NULL && ptr != 0)
	{
		tmp = ft_itoabase((unsigned long int)ptr, "0123456789abcdef");
		if (tmp != NULL)
		{
			ft_putstr(tmp);
			free_ptr(tmp, FALSE);
		}
		else
			ft_putstr("0");
	}
	else
		ft_putstr("0");
}

void	print_shield(t_shield *s)
{
	if (DEBUG_MODE && s->free == FALSE)
		ft_putstr("[U] ");
	else if (s->free == FALSE)
		ft_putstr("");
	else if (DEBUG_MODE)
		ft_putstr("[F] ");
	else
		return ;
	print_pointer(s->ptr);
	ft_putstr(" - ");
	print_pointer(s->ptr + s->size);
	ft_putstr(" : ");
	ft_putnbr(s->size);
	ft_putstr(" octets\n");
}

size_t	print_zone(char *zone, t_map *map, BOOLEAN first)
{
	t_shield	*s;
	size_t		size;

	size = 0;
	s = map->data;
	(void)first;
	if (first == TRUE)
	{
		ft_putstr(zone);
		ft_putstr(" : ");
		print_pointer(map->ptr);
		ft_putstr("\n");
	}
	while (s)
	{
		print_shield(s);
		if (s->free == FALSE)
			size += s->size;
		s = get_shield_id(map, s->id + 1);
	}
	return (size);
}
