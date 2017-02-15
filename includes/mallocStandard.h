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

#ifndef MALLOC_STANDARD_H
# define MALLOC_STANDARD_H
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

# define TINY 1000
# define SMALL 10000

# define ZONE_SIZE 100

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);

/*
** Functions
*/
void					*ft_mmap(void *addr, size_t length, int prot, int flags);
t_sheald				*check_zones(size_t size, t_sheald *left);
void					place_sheald_to_end(t_sheald *s, size_t size);

t_sheald				*malloc_small();
t_sheald				*malloc_large(size_t size);

/*
** Library :
*/
void					ft_print(char *str);


void	*test_malloc(size_t size);

#endif
