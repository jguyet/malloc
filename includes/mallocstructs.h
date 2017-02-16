/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocstructs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jguyet <jguyet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/15 22:53:30 by jguyet            #+#    #+#             */
/*   Updated: 2017/02/15 22:53:32 by jguyet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOCSTRUCTS_H
# define MALLOCSTRUCTS_H

/*
** types de zones existantes
*/
typedef enum			e_zone
{
	ZONE_TINY = 0,
	ZONE_SMALL,
	ZONE_LARGE,
	SIZEOF_ZONE
}						t_zone;

/*
** listes des boucliers de zones reserver
** dans les maps
*/
typedef struct			s_shield
{
	size_t				size;
	void				*ptr;
	struct s_shield		*next;
	struct s_shield		*left;
	int					free;
}						t_shield;

/*
** listes des maps TINY, SMALL, LARGE
*/
typedef struct			s_map
{
	struct s_shield		*data;
	struct s_map		*next;
	struct s_map		*left;
	enum e_zone			zone;
	int					first;
}						t_map;

#endif
