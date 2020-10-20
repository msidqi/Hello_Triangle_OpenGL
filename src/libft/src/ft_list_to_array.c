/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_to_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:51:56 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/20 20:34:20 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lst_to_arr(t_list *head, size_t list_size, size_t type_size)
{
	char	*vertices_array;
	t_list	*iterator;
	size_t	i;

	if (!type_size || !list_size || !head
		|| !(vertices_array = ft_memalloc(type_size * list_size)))
		return (NULL);
	i = list_size - 1;
	iterator = head;
	while (iterator)
	{
		ft_memcpy(vertices_array + i * type_size,
							(const void *)iterator->content, type_size);
		i--;
		iterator = iterator->next;
	}
	return ((void *)vertices_array);
}
