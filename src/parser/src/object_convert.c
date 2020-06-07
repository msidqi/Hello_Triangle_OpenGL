/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:16 by msidqi            #+#    #+#             */
/*   Updated: 2020/06/07 17:04:04 by msidqi           ###   ########.fr       */
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

int				ft_convert_object(t_obj *obj)
{
	if (!obj || obj->vertices_len < 3 || obj->indices_len < 3)
		return (0);
	float *vertices_array = (float *)ft_lst_to_arr(obj->vertices, (size_t)obj->vertices_len, sizeof(float) * 3);
	ft_print_vertices_array(obj, vertices_array);
	ft_lstdel(&obj->vertices, ft_delete_content);
	free(vertices_array);

	unsigned int *vindices_array = ft_lst_to_vindices(obj->indices, (size_t)obj->indices_len);
	ft_print_vindices_array(obj, vindices_array);
	ft_lstdel(&obj->indices, ft_delete_face);
	free(vindices_array);

	return (1);
}