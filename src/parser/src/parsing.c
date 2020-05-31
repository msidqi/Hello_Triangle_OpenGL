#include "parser.h"

void			ft_parse_geometric_vertex(char *line, t_list **vertices)
{
	char	**arr;
	size_t	n;
	t_vec4f	*vertex;

	n = ft_strlsplit(line, ' ', &arr);
	if (n != 4 && n != 5 || !(vertex = (t_vec4f *)ft_memalloc(sizeof(t_vec4f))))
	{
		ft_free_tab(&arr);
		ft_putendl_fd("ft_parse_geometric_vertex(): skiped invalid vertex", 2);
		return ;
	}
	// (x,y,z[,w]) w default: 1.0
	(*vertex) = (t_vec4f){ft_atof(arr[1]), ft_atof(arr[2]), ft_atof(arr[3]),
				n == 5 ? ft_atof(arr[4]) : 1.0};
	ft_lstadd(vertices, ft_lstnew((const void *)vertex, sizeof(t_vec4f)));
	ft_free_tab(&arr);
}

static void		ft_parse_index(const char *index_line, t_face *face, size_t arr_len)
{
	char	**index_components;
	size_t	n_components;
	int		j;

	n_components = ft_strlsplit(index_line, '/', &index_components);
	n_components = n_components > 3 ? 3 : n_components; // max 3 elements in single component of an index (vindex/nindex/tindex/)
	// printf("%s, %s, %s, %s\n", index_components[0], index_components[1], index_components[2]);
	if (n_components == 0 || !(face->vindices = ft_memalloc(sizeof(size_t) * (arr_len - 1))))
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

size_t		ft_get_face_components(size_t values[3], char *index_line)
{
	size_t flag;
	char *found[2];

	flag = 0;
	found[0] = ft_strchr(index_line, '/');
	found[1] = ft_strchr(found[0] ? (found[0] + 1) : "", '/');
	if (index_line && (values[0] = ft_atoi(index_line)))
		flag = flag | F_INDEX;
	else
		values[0] = 0;
	if (found[0] && (values[1] = ft_atoi(found[0] + 1)))
		flag = flag | F_TEXTURE_COORDS;
	else
		values[1] = 0;
	if (found[1] && (values[2] = ft_atoi(found[1] + 1)))
		flag = flag | F_NORMAL;
	else
		values[2] = 0;
	return (flag);
}

void		ft_destroy_face(t_face **face)
{
	if ((*face)->flags & F_INDEX)
		free((*face)->vindices);
	if ((*face)->flags & F_TEXTURE_COORDS)
		free((*face)->vtexture);
	if ((*face)->flags & F_NORMAL)
		free((*face)->vnormals);
	ft_memdel((void **)&(*face));
}

void 		ft_store_face_component(t_face *face, size_t i, size_t values[3])
{
	if ((face->flags & F_INDEX) && values[0])
		face->vindices[i] = values[0];
	if ((face->flags & F_TEXTURE_COORDS) && values[1])
		face->vtexture[i] = values[1];
	if ((face->flags & F_NORMAL) && values[2])
		face->vnormals[i] = values[2];
}

void			ft_parse_indices(char *line, t_list **indices)
{
	t_face	*face;
	char	**splited_line;
	size_t	split_len;
	size_t	index_comps[3];
	int		i;
	size_t	flags;

	split_len = ft_strlsplit(line, ' ', &splited_line); // f 16/2/1 2/3/4 3/5/6 17/7/8 v1/vt1/vn1
	if (split_len < 5 || !(face = (t_face *)ft_memalloc(sizeof(t_face))))
	{
		ft_free_tab(&splited_line);
		return ;
	}
	face->n_of_indices = split_len - 1;
	i = 1; //skip cmd at splited_line[0]
	face->flags = ft_get_face_components(index_comps, splited_line[i]);
	if (face->flags & F_INDEX)
		face->vindices = ft_memalloc(sizeof(size_t) * face->n_of_indices);
	if (face->flags & F_TEXTURE_COORDS)		
		face->vtexture = ft_memalloc(sizeof(size_t) * face->n_of_indices);
	if (face->flags & F_NORMAL)
		face->vnormals = ft_memalloc(sizeof(size_t) * face->n_of_indices);
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
	if (face)
		ft_lstadd(indices, ft_lstnew((const void *)face, sizeof(t_face)));
	ft_free_tab(&splited_line);
}
