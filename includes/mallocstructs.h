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

#ifndef MALLOC_STRUCTS_H
# define MALLOC_STRUCTS_H

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
typedef struct			s_sheald
{
	size_t				size;
	void				*data;
	struct s_sheald		*next;
	struct s_sheald		*left;
	int					free;
}						t_sheald;

/*
** listes des maps TINY, SMALL, LARGE
*/
typedef struct			s_map
{
	struct s_sheald		*data;
	struct s_map		*next;
	struct s_map		*left;
	enum e_zone			zone;
}						t_map;

# define SHEALD_SIZEOF sizeof(struct s_sheald)
# define MAP_SIZEOF sizeof(struct s_map)

#endif
