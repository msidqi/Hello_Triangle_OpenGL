#include "parser.h"

void			ft_print_vertices(t_obj *obj)
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
		printf("(% f, % f, % f, % f)\n",
		vertex->x, vertex->y,
		vertex->z, vertex->w);
		head = head->next;
	}
}

static void		ft_print_array(char *name, unsigned int *array, unsigned int len)
{
	unsigned int	i;

	i = -1;
	printf("%s [ ", name);
	while (++i < len)
		printf(i != len - 1 ? "%3u, " : "%3u ]\n", array[i]);
}

void			ft_print_indices(t_obj *obj)
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
		if (face->flags & F_TEXTURE_INDEX)
			ft_print_array("vtexture", face->vtexture, face->n_of_indices);
		if (face->flags & F_NORMAL)
			ft_print_array("vnormal", face->vnormals, face->n_of_indices);
		head = head->next;
		printf("-----------------\n");
	}
}

static void		ft_vertices_array_no_tex(t_obj *obj)
{
	int i;
	
	i = -1;
	printf("number of vertices: %u | number of floats %u\n",
	obj->vertices_len, obj->vertices_len * 3);
	while (++i < obj->vertices_len * 3)
	{
		if (i % 3 == 0)
			printf("\nvertices_array ");
		printf("% f ", obj->vertices_array[i]);
	}
	printf("\nconfirmed vindices len %d (should be %u)\n----------------------\n",
	i, obj->vertices_len * 3);
}

static void		ft_vertices_array_with_tex(t_obj *obj)
{
	int i;
	
	i = -1;
	printf("number of vertices: %u | number of floats (including tex) %u\n",
	obj->vertices_len, obj->vertices_len * 5);
	while (++i < obj->vertices_len * 5)
	{
		if (i % 5 == 0)
			printf(" ]\nvertices_arr [ ");
		printf("% -.8f ,", obj->vertices_array[i]);
	}
	printf("\nconfirmed vindices len %d (should be %u)\n----------------------\n",
	i, obj->vertices_len * 5);
}

void		ft_print_vertices_array(t_obj *obj)
{
	if (obj->flags == 1)
		ft_vertices_array_with_tex(obj);
	else
		ft_vertices_array_no_tex(obj);
}

void			ft_print_vindices_array(t_obj *obj, unsigned int *vindices_array)
{
	int i;
	
	i = 0;
	printf("number of vindices: %u | number of unsigned int %u\n",
	obj->indices_len, obj->indices_len * 3 /*face->n_of_indices*/);
	while (i < obj->indices_len * 3)
	{
		ft_print_array("vindices_array", vindices_array + i, 3);
		i += 3;
	}
	printf("confirmed vindices len %d (should be %u)\n----------------------\n",
	i, obj->indices_len * 3 /*face->n_of_indices*/);
}
