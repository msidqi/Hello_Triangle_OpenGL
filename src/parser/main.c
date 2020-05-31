#include "parser.h"

int main(int argc, char **argv)
{
	t_obj	*obj;
	char	*full_path;

	if (argc < 2)
	{
		ft_putendl_fd("Usage: ./parseObj OBJ_PATH", 2);
		return (0);
	}
	full_path = argv[1];
	if (!full_path || !(obj = ft_obj_from_file(full_path)))
	{
		perror("ft_obj_from_file()");
		return (0);
	}
	ft_print_indices(obj);
	// ft_print_vertices(obj);
	ft_destroy_object(&obj);
	// ctnr.obj_lst = NULL;
	// ft_lstadd(&ctnr.obj_lst, obj); // add object to main list
	// ft_lstmap(ctnr.obj_lst, ); free objects
	return (0);
}