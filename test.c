/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 17:48:29 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/13 17:49:24 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mallocstandard.h>
#include <stdio.h>
//#include <stdlib.h>

void	test()
{
	char* test;

	test = NULL;
	if ((test = (char*)malloc(9 * sizeof(char))) == NULL)
	{
		printf("lol");
		return ;
	}
	free(test);
}

int		main(int argc, char **argv)
{ 
	int i = 0;
	while (i < 103)
	{
    	char *str2 = malloc(100000);
    	i++;
	}
    return (0);
}
