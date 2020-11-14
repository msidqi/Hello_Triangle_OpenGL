/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:28 by msidqi            #+#    #+#             */
/*   Updated: 2020/11/14 12:57:30 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_cmd	*ft_get_command(t_cmd *this)
{
	ssize_t index;

	if (!this->to_parse || (index = ft_str_index_of(this->to_parse, ' ')) <= 0)
		this->cmd_code = C_SKIP;
	else if (!ft_strncmp(this->to_parse, "#", (size_t)index))
		this->cmd_code = C_SKIP;
	else if (!ft_strncmp(this->to_parse, "f", (size_t)index))
		this->cmd_code = C_VERTEX_INDEX;
	else if (!ft_strncmp(this->to_parse, "v", (size_t)index))
		this->cmd_code = C_GEOMETRIC_VERTEX;
	else if (!ft_strncmp(this->to_parse, "vt", (size_t)index))
		this->cmd_code = C_TEXTURE_COORD;
	else
		this->cmd_code = C_SKIP;
	return (this);
}

static void		ft_destory_command(t_cmd **this)
{
	if (this)
	{
		if ((*this)->to_parse)
			ft_memdel((void **)&(*this)->to_parse);
		ft_memdel((void **)&(*this));
	}
}

/*
** returns 1 on successful parse and storing of line
** 0 on skip (null to_parse, invalid command, comment command)
** -1 on uninitialized command
*/

static int		ft_command_exec(t_cmd *this, t_obj *obj)
{
	t_vec4f *vertex;

	if (this->cmd_code == C_UNINITIALIZED)
		return (-1);
	if (this->cmd_code == C_SKIP)
	{
		ft_memdel((void **)&this->to_parse);
		return (0);
	}
	if (this->cmd_code == C_GEOMETRIC_VERTEX &&
	(vertex = this->parse_geometric_vertex(this->to_parse, &obj->vertices)))
	{
		ft_vec3f_add_a(&obj->center, (*(t_vec3f *)vertex));
		obj->vertices_len++;
	}
	if (this->cmd_code == C_TEXTURE_COORD &&
		this->parse_texture_coords(this->to_parse, &obj->tex_coords))
		obj->tex_len++;
	if (this->cmd_code == C_VERTEX_INDEX &&
		this->parse_indices(this->to_parse, &obj->indices, &obj->indices_len))
		obj->indices_len++;
	ft_memdel((void **)&this->to_parse);
	this->cmd_code = C_SKIP;
	return (1);
}

t_cmd			*ft_command_construct(void)
{
	t_cmd	*c;

	if (!(c = (t_cmd *)ft_memalloc(sizeof(t_cmd))))
		return (NULL);
	c->parse_texture_coords = &ft_parse_texture_coordinates;
	c->parse_geometric_vertex = &ft_parse_geometric_vertex;
	c->parse_indices = &ft_parse_indices;
	c->get = &ft_get_command;
	c->exec = &ft_command_exec;
	c->cmd_code = -1;
	c->destroy = &ft_destory_command;
	return (c);
}
