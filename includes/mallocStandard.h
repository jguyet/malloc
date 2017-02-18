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

# include <unistd.h>

# ifdef MALLOC_PROG

# include <stdlib.h>
# include <sys/mman.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/resource.h>

# include "mallocstructs.h"

# include <stdio.h>

# define TRUE 1
# define FALSE 0
# define BOOLEAN int

# define ZONE_MAX_SIZE 100
# define PAGE_SIZE getpagesize()
# define TINY (PAGE_SIZE / 4) * ZONE_MAX_SIZE
# define SMALL (1 * PAGE_SIZE) * ZONE_MAX_SIZE

# define DEBUG_MODE FALSE
/*
** Functions
*/
t_shield				*get_shield(size_t size);
t_shield				*add_clean_shield(void *ptr);
void					*ft_mmap(void *addr, size_t length, int prot,\
						int flags);
t_zone					get_zone_type_by_size(size_t size);
t_map					*getallmaps(void);
t_map					*newmap(t_map *map, t_zone zone, int large_size);
BOOLEAN					haszone(t_zone zone);
t_map					*getmap_by_zone(t_zone zone);
t_shield				*check_free_place(t_zone zone, size_t size);
t_map					*add_new_map(t_zone zone, int large_size);
t_shield				*get_free_shield(t_map *map, size_t size);
size_t					get_used_size(t_map *map);
size_t					get_free_size(t_map *map);
void					find_and_free_map(void);
t_map					**getfirstmap(void);

/*
** Alocations de zones fraiche
*/
t_shield				*malloc_tiny();
t_shield				*malloc_small();
t_shield				*malloc_large(size_t size);

# endif

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					show_alloc_mem(void);
/*
** Library :
*/
void					ft_print(char *str);

#endif
