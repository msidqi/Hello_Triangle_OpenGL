/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:16 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/22 20:49:40 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void			ft_error(char *message)
{
	ft_putendl_fd(message, 2);
}

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
		while (++j < 3)
			vindices_array[i++] = face->vindices[j];
		iterator = iterator->next;
	}
	return (vindices_array);
}

void			*ft_lst_to_vindices_pthread(void *param)
{
	t_obj			*obj;
	t_list			*iterator;
	size_t			i;

	obj = (t_obj *)param;
	if (!obj->indices_len || !obj->indices || !(obj->vindices_array =
				ft_memalloc(sizeof(unsigned int) * obj->indices_len * 3)))
		return (NULL);
	i = 0;
	iterator = obj->indices;
	while (iterator)
	{
		if (!iterator->content || !((t_face *)iterator->content)->vindices)
		{
			ft_error("lst_to_vindices(): read attempt from (nil) (t_face)content");
			ft_memdel((void **)&obj->vindices_array);
			return (NULL);
		}
		ft_memcpy((void *)(obj->vindices_array + i),
		(void *)((t_face *)iterator->content)->vindices,sizeof(unsigned int) * 3 /*face->n_of_indices */);
		i += 3;
		iterator = iterator->next;
	}
	ft_lstdel(&obj->indices, ft_delete_face);
	return (NULL);
}

static void		ft_lst_to_arr_with_textures(t_obj	*obj)
{
	t_list	*vert_iter;
	t_list	*tex_iter;
	size_t	i;

	i = obj->vertices_len - 1;
	vert_iter = obj->vertices;
	tex_iter = obj->tex_coords;
	if (!tex_iter || !vert_iter
		|| !(obj->vertices_array =
			ft_memalloc(sizeof(float) * 5 * obj->vertices_len)))
		return ;
	while (vert_iter && tex_iter)
	{
		ft_memcpy((obj->vertices_array + i * 5),
		(const void *)vert_iter->content, sizeof(float) * 3);
		ft_memcpy((obj->vertices_array + i * 5 + 3),
		(const void *)tex_iter->content, sizeof(float) * 2);
		i--;
		vert_iter = vert_iter->next;
		tex_iter = tex_iter->next;
	}
}

void			*ft_lst_to_vertices_pthread(void *param)
{
	t_obj	*obj;
	
	obj = (t_obj *)param;
	if (obj->vertices_len <= obj->tex_len && obj->tex_len > 0)
	{
		ft_lst_to_arr_with_textures(obj);
		obj->flags = F_INDEX | F_TEXTURE_INDEX;
	}
	else
	{
		obj->vertices_array = (float *)ft_lst_to_arr(obj->vertices,
						(size_t)obj->vertices_len, sizeof(float) * 3);
		obj->tex_len = 0;
		obj->flags = F_INDEX;
	}
	ft_lstdel(&obj->tex_coords, ft_delete_content);
	ft_lstdel(&obj->vertices, ft_delete_content);
	return (NULL);
}

int				ft_convert_object(t_obj *obj)
{
	pthread_t id[2];

	ft_putendl_fd("converting object...", 1);
	if (!obj || obj->vertices_len < 3 || obj->indices_len < 2)
	{
		ft_putendl_fd("Error: Could not convert object", 2);
		return (0);
	}
	pthread_create(&id[0], NULL, ft_lst_to_vindices_pthread, (void *)obj);
	pthread_create(&id[1], NULL, ft_lst_to_vertices_pthread, (void *)obj);
	pthread_join(id[0], NULL);
	pthread_join(id[1], NULL);
	if (!obj->vertices_array || !obj->vindices_array)
	{
		ft_putendl_fd("Error: Object was not converted", 2);
		return (0);
	}
	ft_putendl_fd("converting object done.", 1);
	return (1);
}
