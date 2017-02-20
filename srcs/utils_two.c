/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 18:29:44 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/20 18:29:45 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MALLOC_PROG
#include "mallocstandard.h"

int			get_count_zone(t_zone zone)
{
	t_map	*map;
	int		count;

	map = getallmaps();
	count = 0;
	while (map)
	{
		if (map->first == FALSE && map->zone == zone)
			count++;
		map = map->next;
	}
	return (count);
}
