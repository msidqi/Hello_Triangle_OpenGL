/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_geometry_vertex.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:10:25 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/29 17:10:36 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** (*vertex) = (x,y,z[,w]) w default: 1.0
*/

unsigned int	ft_parse_geometric_vertex(char *line, t_list **vertices)
{
	char			**arr;
	unsigned int	n;
	t_vec4f			*vertex;

	n = (unsigned int)ft_strlsplit(line, ' ', &arr);
	if ((n != 4 && n != 5) ||
	!(vertex = (t_vec4f *)ft_memalloc(sizeof(t_vec4f))))
	{
		ft_free_tab(&arr);
		ft_stderr("ft_parse_geometric_vertex(): skiped invalid vertex");
		return (0);
	}
	(*vertex) = (t_vec4f){ft_atof(arr[1]), ft_atof(arr[2]), ft_atof(arr[3]),
				n == 5 ? ft_atof(arr[4]) : 1.0};
	ft_lstadd(vertices, ft_lstnew((const void *)vertex, sizeof(t_vec4f)));
	ft_free_tab(&arr);
	return (1);
}

/*
** (*coords) = // (x,y)
*/

unsigned int	ft_parse_texture_coordinates(char *line, t_list **tex_coords)
{
	char			**arr;
	unsigned int	n;
	t_vec2f			*coords;

	n = (unsigned int)ft_strlsplit(line, ' ', &arr);
	if ((n < 3) || !(coords = (t_vec2f *)ft_memalloc(sizeof(t_vec2f))))
	{
		ft_free_tab(&arr);
		ft_stderr("ft_parse_texture_coordinates(): skiped invalid coords");
		return (0);
	}
	(*coords) = (t_vec2f){ft_atof(arr[1]), ft_atof(arr[2])};
	ft_lstadd(tex_coords, ft_lstnew((const void *)coords, sizeof(t_vec2f)));
	ft_free_tab(&arr);
	return (1);
}
