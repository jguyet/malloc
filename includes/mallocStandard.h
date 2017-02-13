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
# include <sys/mman.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/resource.h>

typedef enum			e_prot
{
	EXEC = PROT_EXEC,
	READ = PROT_READ,
	WRITE = PROT_WRITE,
	NONE = PROT_NONE,
	PROT_LENGTH = 5
}						t_prot;

void					free(void *ptr);
void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);

/*
** Functions
*/
void					*ft_mmap(void *addr, size_t length, int prot, int flags);

/*
** Library :
*/
void					ft_print(char *str);

void	*test_malloc(size_t size);

#endif
