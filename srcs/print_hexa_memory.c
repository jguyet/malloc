/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa_memory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 16:39:53 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/21 16:39:55 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MALLOC_PROG
#include "mallocstandard.h"

int		print_hexa_shield(t_shield *s)
{
	void	*ptr;
	size_t	i;
	size_t	count;

	ptr = s->ptr;
	i = 0;
	count = 0;
	while (i < s->size)
	{
		if (s->free == FALSE)
		{
			print_itoa_val((*(char*)ptr) >> 4);
			print_itoa_val((char)(*(char*)ptr) - (((*(char*)ptr) >> 4) << 4));
			ft_putstr(" ");
			count++;
			if (count >= 16)
				count = print_ended_hexa_line(count, ptr);
		}
		ptr++;
		i++;
	}
	return (print_ended_hexa_line(count, ptr));
}

void	print_preshexa_shield(t_shield *s)
{
	size_t	count;

	print_shield(s);
	ft_putstr("00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F");
	ft_putstr("  | 0123456789ABCDEF\n");
	count = print_hexa_shield(s);
	if (count > 0)
		ft_putstr("\n");
}

void	print_hexa_map(t_map *map)
{
	t_shield *s;

	s = map->data;
	while (s)
	{
		if (s->free == FALSE)
			print_preshexa_shield(s);
		s = get_shield_id(map, s->id + 1);
	}
}

void	print_hexa_zone(t_zone zone)
{
	t_map *map;

	map = getallmaps();
	while (map)
	{
		if (map->first == FALSE && map->zone == zone)
		{
			print_hexa_map(map);
		}
		map = map->next;
	}
}
