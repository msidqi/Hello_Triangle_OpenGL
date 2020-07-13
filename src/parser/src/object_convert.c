/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:16 by msidqi            #+#    #+#             */
/*   Updated: 2020/07/13 01:05:57 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

unsigned int	*ft_lst_to_vindices(t_list *head, size_t list_size)
{
	unsigned int	*vindices_array;
	t_list			*iterator;
	t_face			*face;
	size_t			i;
	size_t			j;

	if (!list_size || !head
		|| !(vindices_array = ft_memalloc(sizeof(unsigned int) * list_size * 3)))
		return (NULL);
	// i = list_size - 1;
	i = 0;
	iterator = head;
	while (iterator)
	{
		if (!iterator->content || !((t_face *)iterator->content)->vindices)
		{
			ft_putendl_fd("ft_lst_to_vindices(): read attempt from (nil) (t_face)content", 2);
			return (NULL);
		}
		face = (t_face *)iterator->content;
		j = -1;
		while (++j < 3)//face->n_of_indices
			vindices_array[i++] = face->vindices[j];
		iterator = iterator->next;
	}
	return (vindices_array);
}

void			*ft_lst_to_vindices_pthread(void *param)
{
	t_obj			*obj = (t_obj *)param;
	t_list			*iterator;
	t_face			*face;
	size_t			i;
	size_t			j;

	if (!obj->indices_len || !obj->indices
		|| !(obj->vindices_array = ft_memalloc(sizeof(unsigned int) * obj->indices_len * 3)))
		return (NULL);
	i = 0;
	iterator = obj->indices;
	while (iterator)
	{
		if (!iterator->content || !((t_face *)iterator->content)->vindices)
		{
			ft_putendl_fd("ft_lst_to_vindices(): read attempt from (nil) (t_face)content", 2);
			ft_memdel((void **)&obj->vindices_array);
			return (NULL);
		}
		face = (t_face *)iterator->content;
		j = -1;
		while (++j < 3)//face->n_of_indices
			obj->vindices_array[i++] = face->vindices[j];
		iterator = iterator->next;
	}
	ft_lstdel(&obj->indices, ft_delete_face);
	return (NULL);
}

void			*ft_lst_to_vertices_pthread(void *param)
{
	t_obj	*obj = (t_obj *)param;
	t_list	*iterators[2];
	size_t	i;

	if (obj->vertices_len <= obj->tex_len && obj->tex_len > 0)
	{
		iterators[0] = obj->vertices;
		iterators[1] = obj->tex_coords;
		if (!iterators[1] || !iterators[0]
			|| !(obj->vertices_array = ft_memalloc(sizeof(float) * 5 * obj->vertices_len)))
			return (NULL);
		i = obj->vertices_len - 1;
		while (iterators[0] && iterators[1])
		{
			obj->vertices_array[i * 5 + 0] = ((float *)iterators[0]->content)[0];
			obj->vertices_array[i * 5 + 1] = ((float *)iterators[0]->content)[1];
			obj->vertices_array[i * 5 + 2] = ((float *)iterators[0]->content)[2];
			obj->vertices_array[i * 5 + 3] = ((float *)iterators[1]->content)[0];
			obj->vertices_array[i * 5 + 4] = ((float *)iterators[1]->content)[1];
			// ft_memcpy(obj->vertices_array + i * sizeof(float) * 5, (const void *)iterators[0]->content, sizeof(float) * 3);
			// ft_memcpy(obj->vertices_array + i * sizeof(float) * 5 + sizeof(float) * 3, (const void *)iterators[1]->content, sizeof(float) * 2);
			// ft_memcpy(obj->vertices_array + i * sizeof(float) * 3, (const void *)iterators[0]->content, sizeof(float) * 3);
			i--;
			iterators[0] = iterators[0]->next;
			iterators[1] = iterators[1]->next;
		}
		obj->flags = F_INDEX | F_TEXTURE_INDEX;
	}
	else
	{
		obj->vertices_array = (float *)ft_lst_to_arr(obj->vertices, (size_t)obj->vertices_len, sizeof(float) * 3);
		obj->tex_len = 0;
		obj->flags = F_INDEX;
	}
	ft_lstdel(&obj->tex_coords, ft_delete_content);
	ft_lstdel(&obj->vertices, ft_delete_content);
	return (NULL);
}

int				ft_convert_object(t_obj *obj)
{
	ft_putendl_fd("converting object...", 1);
	if (!obj || obj->vertices_len < 3 || obj->indices_len < 2)
		return (0);
	pthread_t id[2];
	pthread_create(&id[0], NULL, ft_lst_to_vindices_pthread, (void *)obj);
	pthread_create(&id[1], NULL, ft_lst_to_vertices_pthread, (void *)obj);
	pthread_join(id[0], NULL);
	pthread_join(id[1], NULL);
	if (!obj->vertices_array || !obj->vindices_array)
		return (0);
	ft_putendl_fd("converting object done.", 1);
	return (1);
}

