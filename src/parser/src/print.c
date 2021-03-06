#include "parser.h"

void	ft_print_vertices(t_obj *obj)
{
	t_list	*head;
	t_vec4f	*vertex;

	if (!obj || !obj->vertices)
	{
		ft_putendl_fd("ft_print_vertices(): read attempt read from (nil) vertices", 2);
		return ;
	}
	printf("Number of vertices: | %u |\n", obj->vertices_len);
	head = obj->vertices;
	while (head)
	{
		if (!head->content)
		{
			ft_putendl_fd("ft_print_vertices(): read attempt from (nil) (t_vec4f *)vertices", 2);
			return ;
		}
		vertex = (t_vec4f *)head->content;
		printf("(%f, %f, %f, %f)\n",
		vertex->x, vertex->y,
		vertex->z, vertex->w);
		head = head->next;
	}
}

static void	ft_print_array(char *name, unsigned int *array, unsigned int len)
{
	unsigned int	j;

	j = -1;
	printf("%s [ ", name);
	while (++j < len)
		printf(j != len - 1 ? "%u, " : "%u ]\n", array[j]);
}

void		ft_print_indices(t_obj *obj)
{
	t_list *head;
	t_face *face;

	if (!obj || !obj->indices)
	{
		ft_putendl_fd("ft_print_indices(): read attempt read from (nil) indices", 2);
		return ;
	}
	printf("Number of indices: | %u |\n", obj->indices_len);
	head = obj->indices;
	while (head)
	{
		if (!head->content || !((t_face *)head->content)->vindices)
		{
			ft_putendl_fd("ft_print_indices(): read attempt from (nil) (t_face)content", 2);
			return ;
		}
		face = (t_face *)head->content;
		printf("number of indices: %u\n", face->n_of_indices);
		if (face->flags & F_INDEX)
			ft_print_array("vindices", face->vindices, face->n_of_indices);
		if (face->flags & F_TEXTURE_COORDS)
			ft_print_array("vtexture", face->vtexture, face->n_of_indices);
		if (face->flags & F_NORMAL)
			ft_print_array("vnormal", face->vnormals, face->n_of_indices);
		head = head->next;
		printf("-----------------\n");
	}
}
