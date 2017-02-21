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

void	print_hexa_shield(t_shield *s)
{
	void	*ptr;
	size_t	i;
	//char	*tmp;

	ptr = s->ptr;
	i = 0;
	while (i < s->size)
	{
		if (s->free == FALSE)
		{
			ft_putnbr(*(char*)ptr);
			ft_putstr("\n");
			/*tmp = ft_itoabase((((short)ptr) << 12) >> 12, "0123456789abcdef");
			if (tmp != NULL)
				ft_putstr(tmp);
			else
				ft_putstr("0");
			tmp = ft_itoabase((((short)ptr) << 12) >> 12, "0123456789abcdef");
			if (tmp != NULL)
				ft_putstr(tmp);
			else
				ft_putstr("0");*/
		}
		ptr++;
		i++;
	}
}

void	print_hexa_map(t_map *map)
{
	t_shield *s;

	s = map->data;
	while (s)
	{
		print_hexa_shield(s);
		//if (s->free == FALSE)
		//	size += s->size;
		s = get_shield_id(map, s->id + 1);
	}
}

void	print_hexa_tiny(void)
{
	t_map *map;

	map = getallmaps();
	while (map)
	{
		if (map->first == FALSE && map->zone == ZONE_TINY)
		{
			print_hexa_map(map);
		}
		map = map->next;
	}
}
