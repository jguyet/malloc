/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoabase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:00:47 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/20 19:00:48 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MALLOC_PROG
#include "mallocstandard.h"

static void	*itoa_malloc(size_t size)
{
	t_shield	*result;

	if (size < 1)
		return (NULL);
	if (!(result = get_shield(size)))
		return (NULL);
	result->free = FALSE;
	return (result->ptr);
}

char		*ft_itoabase(long long int nbr, char *base)
{
	char			*res;
	int				size;
	long long int	len;
	long long int	tmp;

	tmp = nbr;
	len = 1;
	size = 0;
	while ((tmp = tmp / ft_strlen(base)))
	{
		len = len * ft_strlen(base);
		size++;
	}
	tmp = nbr;
	res = (char*)itoa_malloc(sizeof(char) * (size + 1));
	size = 0;
	while (len)
	{
		res[size] = base[(tmp / len)];
		tmp = tmp - ((tmp / len) * len);
		len = len / ft_strlen(base);
		size++;
	}
	res[size] = '\0';
	return (res);
}
