/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:28 by msidqi            #+#    #+#             */
/*   Updated: 2020/06/21 23:12:50 by msidqi           ###   ########.fr       */
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
returns 1 on successful parse and storing of line
0 on skip (null to_parse, invalid command, comment command)
-1 on uninitialized command
*/
static int		ft_command_exec(t_cmd *this, t_obj *obj)
{
	if (this->cmd_code == C_UNINITIALIZED)
	{
		perror("ft_command_exec()");
		return (-1);
	}
	if (this->cmd_code == C_SKIP)
	{
		ft_memdel((void **)&this->to_parse);
		return (0);
	}
	if (this->cmd_code == C_GEOMETRIC_VERTEX &&
		this->parse_geometric_vertex(this->to_parse, &obj->vertices))
		obj->vertices_len++;
	if (this->cmd_code == C_VERTEX_INDEX &&
		this->parse_indices(this->to_parse, &obj->indices, &obj->indices_len))
		obj->indices_len++;
	ft_memdel((void **)&this->to_parse);
	// printf("number of indices %u | number of vertices %u \n", obj->indices_len, obj->vertices_len);
	this->cmd_code = C_SKIP;
	return (1);
}

t_cmd			*ft_command_construct()
{
	t_cmd	*c;

	if (!(c = (t_cmd *)ft_memalloc(sizeof(t_cmd))))
		return (NULL);
	c->parse_geometric_vertex = &ft_parse_geometric_vertex;
	c->parse_indices = &ft_parse_indices;
	c->get = &ft_get_command;
	c->exec = &ft_command_exec;
	c->cmd_code = -1;
	c->destroy = &ft_destory_command;
	return (c);
}
