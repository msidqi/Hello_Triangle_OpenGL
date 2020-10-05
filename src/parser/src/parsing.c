/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:24 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/05 20:59:55 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

unsigned int	ft_parse_geometric_vertex(char *line, t_list **vertices)
{
	char					**arr;
	unsigned int	n;
	t_vec4f				*vertex;

	n = (unsigned int)ft_strlsplit(line, ' ', &arr);
	if ((n != 4 && n != 5) || !(vertex = (t_vec4f *)ft_memalloc(sizeof(t_vec4f))))
	{
		ft_free_tab(&arr);
		ft_putendl_fd("ft_parse_geometric_vertex(): skiped invalid vertex", 2);
		return (0);
	}
	// (x,y,z[,w]) w default: 1.0
	(*vertex) = (t_vec4f){ft_atof(arr[1]), ft_atof(arr[2]), ft_atof(arr[3]),
				n == 5 ? ft_atof(arr[4]) : 1.0};
	ft_lstadd(vertices, ft_lstnew((const void *)vertex, sizeof(t_vec4f)));
	ft_free_tab(&arr);
	return (1);
}

unsigned int	ft_parse_texture_coordinates(char *line, t_list **tex_coords)
{
	char			**arr;
	unsigned int	n;
	t_vec2f			*coords;

	n = (unsigned int)ft_strlsplit(line, ' ', &arr);
	if ((n < 3) || !(coords = (t_vec2f *)ft_memalloc(sizeof(t_vec2f))))
	{
		ft_free_tab(&arr);
		ft_putendl_fd("ft_parse_texture_coordinates(): skiped invalid coords", 2);
		return (0);
	}
	// (x,y)
	(*coords) = (t_vec2f){ft_atof(arr[1]), ft_atof(arr[2])};
	ft_lstadd(tex_coords, ft_lstnew((const void *)coords, sizeof(t_vec2f)));
	ft_free_tab(&arr);
	return (1);
}

unsigned int	ft_get_face_components(unsigned int values[3], char *index_line)
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

void 			ft_store_face_component(t_face *face, unsigned int i, unsigned int values[3])
{
	if ((face->flags & F_INDEX) && values[0])
		face->vindices[i] = values[0] < 0 ? 0 : values[0] - 1;
	if ((face->flags & F_TEXTURE_INDEX) && values[1])
		face->vtexture[i] = values[1];
	if ((face->flags & F_NORMAL) && values[2])
		face->vnormals[i] = values[2];
}

void			ft_multi_face(t_face *face, t_list **indices)
{
	t_face *new_face[2];

	new_face[0] = (t_face *)ft_memalloc(sizeof(t_face));
	new_face[0]->flags = face->flags;
	new_face[0]->n_of_indices = 3;
	new_face[1] = (t_face *)ft_memalloc(sizeof(t_face));
	new_face[1]->flags = face->flags;
	new_face[1]->n_of_indices = 3;
	if ((face->flags & F_INDEX))
	{
		new_face[0]->vindices = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 3);
		new_face[0]->vindices[0] = face->vindices[0];
		new_face[0]->vindices[1] = face->vindices[2];
		new_face[0]->vindices[2] = face->vindices[3];
		new_face[1]->vindices = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 3);
		ft_memmove(new_face[1]->vindices, face->vindices, sizeof(unsigned int) * 3);
	}
	if ((face->flags & F_TEXTURE_INDEX))
	{
		new_face[0]->vtexture = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 3);
		new_face[0]->vtexture[0] = face->vtexture[0];
		new_face[0]->vtexture[1] = face->vtexture[2];
		new_face[0]->vtexture[2] = face->vtexture[3];
		new_face[1]->vtexture = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 3);
		ft_memmove(new_face[1]->vtexture, face->vtexture, sizeof(unsigned int) * 3);
	}
	if ((face->flags & F_NORMAL))
	{
		new_face[0]->vnormals = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 3);
		new_face[0]->vnormals[0] = face->vnormals[0];
		new_face[0]->vnormals[1] = face->vnormals[2];
		new_face[0]->vnormals[2] = face->vnormals[3];
		new_face[1]->vnormals = (unsigned int *)ft_memalloc(sizeof(unsigned int) * 3);
		ft_memmove(new_face[1]->vnormals, face->vnormals, sizeof(unsigned int) * 3);
	}
	ft_delete_face(face, 0);
	ft_lstadd(indices, ft_lstnew((const void *)new_face[0], sizeof(t_face))); // insert new_face
	ft_lstadd(indices, ft_lstnew((const void *)new_face[1], sizeof(t_face)));
}

unsigned int	ft_parse_indices(char *line, t_list **indices, unsigned int *indices_len)
{
	t_face			*face;
	char			**splited_line;
	unsigned int	split_len;
	unsigned int	index_comps[3];
	unsigned int	i;
	unsigned int	flags;

	split_len = (unsigned int)ft_strlsplit(line, ' ', &splited_line); // f v1/vt1/vn1
	if (split_len < 4 || !(face = (t_face *)ft_memalloc(sizeof(t_face))))
	{
		ft_free_tab(&splited_line);
		return (0);
	}
	face->n_of_indices = split_len - 1;
	i = 1; //skip cmd at splited_line[0]
	face->flags = ft_get_face_components(index_comps, splited_line[i]);
	if (face->flags & F_INDEX)
		face->vindices = ft_memalloc(sizeof(unsigned int) * face->n_of_indices);
	if (face->flags & F_TEXTURE_INDEX)
		face->vtexture = ft_memalloc(sizeof(unsigned int) * face->n_of_indices);
	if (face->flags & F_NORMAL)
		face->vnormals = ft_memalloc(sizeof(unsigned int) * face->n_of_indices);
	ft_store_face_component(face, i - 1, index_comps);
	while (++i < split_len)
	{
		flags = ft_get_face_components(index_comps, splited_line[i]);
		if (face->flags != flags)
		{
			ft_destroy_face(&face);
			break ;
		}
		ft_store_face_component(face, i - 1, index_comps);
	}
	ft_free_tab(&splited_line);
	if (face)
	{
		if (face->n_of_indices == 4)
		{
			ft_multi_face(face, indices);
			(*indices_len)++;
			// printf("need to split this\n");
		}
		else // insert original face
			ft_lstadd(indices, ft_lstnew((const void *)face, sizeof(t_face)));
		return (1);
	}
	return (0);
}
