/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa_memory_suite.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/21 19:11:04 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/21 19:11:05 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MALLOC_PROG
#include "mallocstandard.h"

void	print_ascii_sixten_shield(int size, void *ptr)
{
	int i;

	i = 0;
	while (i < size && i < 16)
	{
		if ((*(char*)ptr) > 33 && (*(char*)ptr) < 127)
			ft_putchar((*(char*)ptr));
		else
			ft_putchar('.');
		ptr++;
		i++;
	}
}

void	print_itoa_val(int val)
{
	char	*tmp;

	tmp = ft_itoabase(val, "0123456789ABCDEF");
	if (tmp != NULL)
	{
		ft_putstr(tmp);
		free(tmp);
	}
	else
		ft_putstr("0");
}

int		print_ended_hexa_line(size_t count, void *ptr)
{
	int i;

	i = 0;
	if (count <= 0)
		return (0);
	while (i + count < 16)
	{
		ft_putstr("   ");
		i++;
	}
	ft_putstr(" | ");
	print_ascii_sixten_shield(count, ptr - (count - 1));
	if (count >= 16)
	{
		ft_putstr("\n");
		return (0);
	}
	return (count);
}
