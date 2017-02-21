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
#  include <stdlib.h>
#  include <sys/mman.h>
#  include <pthread.h>
#  include <sys/time.h>
#  include <sys/resource.h>

#  include "mallocstructs.h"

#  define TRUE 1
#  define FALSE 0
#  define BOOLEAN int

#  define ZONE_MAX_SIZE 100
#  define PAGE_SIZE getpagesize()
#  define TINY (PAGE_SIZE / 4) * ZONE_MAX_SIZE
#  define SMALL (10 * PAGE_SIZE) * ZONE_MAX_SIZE

#  define DEBUG_MODE FALSE

/*
** ft_mmap
*/
void			*ft_mmap(void *addr, size_t length, int prot, int flags);
/*
** Functions maps
*/
t_map			*getallmaps(void);
t_map			*newmap(t_map *map, t_zone zone, int large_size);
t_map			*add_new_map(t_zone zone, int large_size);
BOOLEAN			haszone(t_zone zone);
t_map			*getmap_by_zone(t_zone zone);
/*
** Functions utils
*/
size_t			get_used_size(t_map *map);
size_t			get_free_size(t_map *map);
size_t			get_free_number_places(t_map *map);
t_shield		*get_free_shield(t_map *map, size_t size);
size_t			get_size_place(t_zone zone);
/*
** Functions utils_two
*/
int				get_count_zone(t_zone zone);
/*
** Functions shield
*/
void			*get_ptr_id(t_map *map, int id);
t_shield		*get_shield_id(t_map *map, int id);
void			*get_shield_by_id(void *ptr, int id);
void			create_shields(void *ptr, t_zone zone, size_t ssize);
void			add_shield(void *ptr, int id, int size);
/*
** Functions free
*/
void			*get_start_ptr_zone(t_map *map);
void			*get_end_ptr_zone(void *start_p, t_map *map);
BOOLEAN			free_shield(void *ptr, t_map *map);
void			free_map(t_map *map);
void			free_ptr(void *ptr);
/*
** Functions memory_finder
*/
t_shield		*get_shield_new_map(t_zone zone, size_t size);
t_shield		*check_free_place(t_zone zone, size_t size);
t_shield		*get_shield(size_t size);
t_zone			get_zone_type_by_size(size_t size);
/*
** Function Realloc
*/
void			*realloc_memory(void *ptr, size_t size);
/*
** Functions Print
*/
size_t			print_zone(char *zone, t_map *map, BOOLEAN first);
void			print_pointer(void *ptr);
void			print_shield(t_shield *s);
/*
** Functions Print_zone
*/
size_t			print_tiny(void);
size_t			print_small(void);
size_t			print_large(void);
/*
** Library
*/
void			ft_putstr(char *str);
void			ft_putnbr(long int n);
int				ft_strlen(char *str);
char			*ft_itoabase(long long int nbr, char *base);
void			ft_putchar(char c);

void			print_hexa_tiny(void);

pthread_mutex_t	g_lock;

# endif

/*
** MALLOC
*/
void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);
void			show_hexa_mem(void);
/*
** BONUS
*/
void			print_hexa_tiny(void);
#endif
