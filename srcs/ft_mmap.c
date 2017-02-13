/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 17:31:35 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/13 17:31:40 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mallocstandard.h>

void	*ft_mmap(void *addr, size_t length, int prot, int flags)
{
	return (mmap(addr, length, prot, flags | MAP_ANONYMOUS | MAP_PRIVATE, -1, 0));
}
