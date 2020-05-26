#include "parser.h"

static t_cmd_handler	*ft_get_command(t_cmd_handler *this)
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

static void				ft_destory_command(t_cmd_handler **this)
{
	if (this)
	{
		if ((*this)->to_parse)
			ft_memdel((void **)&(*this)->to_parse);
		ft_memdel((void **)&(*this));
	}
}

static void				ft_parse_geometric_vertex(char *line, t_list **vertices)
{
	char	**arr;
	size_t	n;
	t_vec4f	*vertex;

	n = ft_strlsplit(line, ' ', &arr);
	if (n != 4 && n != 5 || !(vertex = (t_vec4f *)ft_memalloc(sizeof(t_vec4f))))
	{
		ft_free_tab(&arr);
		return ;
	}
	// (x,y,z[,w]) w default: 1.0
	(*vertex) = (t_vec4f){ft_atof(arr[1]), ft_atof(arr[2]), ft_atof(arr[3]),
				n == 5 ? ft_atof(arr[4]) : 1.0};
	ft_lstadd(vertices, ft_lstnew((const void *)vertex, sizeof(t_vec4f)));
	printf("vertex %s | arr len %3zu | (%f, %f, %f)\n", line, n, vertex->x, vertex->y, vertex->z);
	ft_free_tab(&arr);
}

static void				ft_parse_vertex_index(char *line, t_list **indices)
{
	// printf("index %s\n", line);
}

int						ft_command_exec(t_cmd_handler *this, t_obj *obj)
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
	if (this->cmd_code == C_GEOMETRIC_VERTEX)
		this->parse_geometric_vertex(this->to_parse, &obj->vertices);
	if (this->cmd_code == C_VERTEX_INDEX)
		this->parse_vertex_index(this->to_parse, &obj->indices);
	ft_memdel((void **)&this->to_parse);
	this->cmd_code = C_SKIP;
	return (1);
}

t_cmd_handler			*ft_command_construct()
{
	t_cmd_handler	*c;

	if (!(c = (t_cmd_handler *)ft_memalloc(sizeof(t_cmd_handler))))
		return (NULL);
	c->parse_geometric_vertex = &ft_parse_geometric_vertex;
	c->parse_vertex_index = &ft_parse_vertex_index;
	c->get = &ft_get_command;
	c->exec = &ft_command_exec;
	c->cmd_code = -1;
	c->destroy = &ft_destory_command;
	return (c);
}
