/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocStandard.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 17:10:07 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/13 17:27:20 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOCSTANDARD_H
# define MALLOCSTANDARD_H
# include <stdlib.h>
# include <unistd.h>
# include <sys/mman.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/resource.h>

# include "mallocstructs.h"

# include <stdio.h>

# define TRUE 1
# define FALSE 0
# define BOOLEAN int

# define TINY 1000
# define SMALL 10000

# define ZONE_MAX_SIZE 100

# define DEBUG_MODE FALSE

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);

/*
** Functions
*/
t_shield				*get_shield(size_t size);
t_shield				*add_clean_shield(void *ptr);
void					*ft_mmap(void *addr, size_t length, int prot,\
						int flags);
t_shield				*check_zone(size_t size, t_shield *s, t_zone zone);
void					place_shield_to_end(t_shield *s, size_t size);
t_zone					get_zone_type_by_size(size_t size);
t_map					*getallmaps(void);
t_map					*newmap(t_map *map, t_zone zone, int large_size);
BOOLEAN					haszone(t_zone zone);
t_map					*getmap_by_zone(t_zone zone);

/*
** Alocations de zones fraiche
*/
t_shield				*malloc_tiny();
t_shield				*malloc_small();
t_shield				*malloc_large(size_t size);

/*
** Library :
*/
void					ft_print(char *str);

void					*test_malloc(size_t size);

#endif
