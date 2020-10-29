/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:08:36 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/29 17:08:52 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void			ft_destroy_face(t_face **face)
{
	if ((*face)->flags & F_INDEX)
		free((*face)->vindices);
	if ((*face)->flags & F_TEXTURE_INDEX)
		free((*face)->vtexture);
	if ((*face)->flags & F_NORMAL)
		free((*face)->vnormals);
	ft_memdel((void **)&(*face));
}

void			ft_store_face_components(
	t_face *face,
	unsigned int i,
	unsigned int values[3])
{
	if ((face->flags & F_INDEX) && values[0])
		face->vindices[i] = values[0] < 0 ? 0 : values[0] - 1;
	if ((face->flags & F_TEXTURE_INDEX) && values[1])
		face->vtexture[i] = values[1];
	if ((face->flags & F_NORMAL) && values[2])
		face->vnormals[i] = values[2];
}

int				ft_allocate_face_components(t_face *face)
{
	if (face->flags & F_INDEX &&
	!(face->vindices = ft_memalloc(sizeof(unsigned int) * face->n_of_indices)))
		return (0);
	if (face->flags & F_TEXTURE_INDEX &&
	!(face->vtexture = ft_memalloc(sizeof(unsigned int) * face->n_of_indices)))
		return (0);
	if (face->flags & F_NORMAL &&
	!(face->vnormals = ft_memalloc(sizeof(unsigned int) * face->n_of_indices)))
		return (0);
	return (1);
}

t_face			*new_face(unsigned int flags, unsigned int n_of_indices)
{
	t_face	*face;

	face = (t_face *)ft_memalloc(sizeof(t_face));
	face->flags = flags;
	face->n_of_indices = n_of_indices;
	return (face);
}
