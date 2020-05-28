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

static void				ft_destory_command(t_cmd **this)
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
	ft_free_tab(&arr);
}

static void				ft_parse_index(const char *index_line, t_face *face)
{
	char	**index_components;
	size_t	n_components;
	int		j;

	n_components = ft_strlsplit(index_line, '/', &index_components);
	n_components = n_components > 3 ? 3 : n_components; // max 3 elements in single component of an index (vindex/nindex/tindex/)
	// printf("%s, %s, %s, %s\n", index_components[0], index_components[1], index_components[2]);
	if (!(face->vindices = ft_memalloc(sizeof(size_t) * n_components)))
	{
		ft_free_tab(&index_components);
		perror("ft_parse_index()");
		return ;
	}
	j = -1;
	while (++j < n_components)
	{
		face->vindices[j] = ft_atoi(index_components[j]);
	}
	ft_free_tab(&index_components);
	// exit(1);
}

static void				ft_parse_indices(char *line, t_list **indices)
{
	char	**splited_line;
	size_t	arr_len;
	t_face	*face;
	int		i;

	arr_len = ft_strlsplit(line, ' ', &splited_line);
	if (arr_len < 5 || !(face = (t_face *)ft_memalloc(sizeof(t_face))))
	{
		ft_free_tab(&splited_line);
		return ;
	}
	// if (!face->flags)
	// 	face->flags = F_INDEX & F_NORMAL & F_TEXTURE_COORDS;
	i = 0;
	while (++i < arr_len)//skip cmd at arr[0]
	{
		// ft_parse_index(splited_line[i], face);
		face->n_of_indices++;
	}
	ft_lstadd(indices, ft_lstnew((const void *)face, sizeof(t_face)));
	ft_free_tab(&splited_line);
}

int						ft_command_exec(t_cmd *this, t_obj *obj)
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
	// if (this->cmd_code == C_VERTEX_INDEX)
	// 	this->parse_indices(this->to_parse, &obj->indices);
	ft_memdel((void **)&this->to_parse);
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
