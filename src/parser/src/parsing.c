/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:24 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/29 17:14:37 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static unsigned int	ft_get_face_components(
	unsigned int values[3],
	char *index_line)
{
	unsigned int	flag;
	char			*found[2];

	flag = 0;
	found[0] = ft_strchr(index_line, '/');
	found[1] = ft_strchr(found[0] ? (found[0] + 1) : "", '/');
	if (index_line && (values[0] = ft_atoi(index_line)))
		flag = flag | F_INDEX;
	else
		values[0] = 0;
	if (found[0] && (values[1] = ft_atoi(found[0] + 1)))
		flag = flag | F_TEXTURE_INDEX;
	else
		values[1] = 0;
	if (found[1] && (values[2] = ft_atoi(found[1] + 1)))
		flag = flag | F_NORMAL;
	else
		values[2] = 0;
	return (flag);
}

static void			ft_split_face(t_face *src, t_face *dst0, t_face *dst1)
{
	if ((src->flags & F_INDEX))
	{
		dst0->vindices = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 3);
		ft_memmove(dst0->vindices, (unsigned int[3]){src->vindices[0],
		src->vindices[2], src->vindices[3]}, sizeof(unsigned int) * 3);
		dst1->vindices = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 3);
		ft_memmove(dst1->vindices, src->vindices, sizeof(unsigned int) * 3);
	}
	if ((src->flags & F_TEXTURE_INDEX))
	{
		dst0->vtexture = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 3);
		ft_memmove(dst0->vtexture, (unsigned int[3]){src->vtexture[0],
		src->vtexture[2], src->vtexture[3]}, sizeof(unsigned int) * 3);
		dst1->vtexture = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 3);
		ft_memmove(dst1->vtexture, src->vtexture, sizeof(unsigned int) * 3);
	}
	if ((src->flags & F_NORMAL))
	{
		dst0->vnormals = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 3);
		ft_memmove(dst0->vnormals, (unsigned int[3]){src->vnormals[0],
		src->vnormals[2], src->vnormals[3]}, sizeof(unsigned int) * 3);
		dst1->vnormals = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 3);
		ft_memmove(dst1->vnormals, src->vnormals, sizeof(unsigned int) * 3);
	}
}

static void			ft_multi_face(t_face *face, t_list **indices)
{
	t_face	*nf[2];

	nf[0] = new_face(face->flags, 3);
	nf[1] = new_face(face->flags, 3);
	ft_split_face(face, nf[0], nf[1]);
	ft_delete_face(face, 0);
	ft_lstadd(indices, ft_lstnew((const void *)nf[0], sizeof(t_face)));
	ft_lstadd(indices, ft_lstnew((const void *)nf[1], sizeof(t_face)));
}

static t_face		*ft_handle_face_components(t_char2d splited)
{
	unsigned int	index_comps[3];
	unsigned int	i;
	t_face			*f;

	if (splited.length < 4 || !(f = (t_face *)ft_memalloc(sizeof(t_face))))
		return (NULL);
	i = 1;
	f->n_of_indices = splited.length - 1;
	f->flags = ft_get_face_components(index_comps, splited.lines[i]);
	if (!ft_allocate_face_components(f))
	{
		ft_destroy_face(&f);
		return (NULL);
	}
	ft_store_face_components(f, i - 1, index_comps);
	while (++i < splited.length)
	{
		if (f->flags != ft_get_face_components(index_comps, splited.lines[i]))
		{
			ft_destroy_face(&f);
			return (NULL);
		}
		ft_store_face_components(f, i - 1, index_comps);
	}
	return (f);
}

/*
** split_len = ft_strlsplit(line, ' ', &splited_line); // f v1/vt1/vn1
**
** i = 1; //skip cmd at splited_line[0]
*/

unsigned int		ft_parse_indices(
	char *line,
	t_list **indices,
	unsigned int *indices_len)
{
	t_face			*face;
	t_char2d		splited;

	splited.length = (unsigned int)ft_strlsplit(line, ' ', &splited.lines);
	face = ft_handle_face_components(splited);
	ft_free_tab(&splited.lines);
	if (face)
	{
		if (face->n_of_indices == 4)
		{
			ft_multi_face(face, indices);
			(*indices_len)++;
		}
		else
			ft_lstadd(indices, ft_lstnew((const void *)face, sizeof(t_face)));
		return (1);
	}
	return (0);
}
