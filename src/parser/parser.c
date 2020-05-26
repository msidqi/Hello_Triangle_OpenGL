#include "parser.h"

t_container ctnr;

t_obj	*ft_obj_from_file(char *path)
{
	int				fd;
	t_cmd_handler	*cmd;
	t_obj 			*obj;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	if (!(obj = (t_obj *)ft_memalloc(sizeof(t_obj))))
		return (NULL);
	if (!(cmd = ft_command_construct()))
	{
		free(obj);
		close(fd);
		return (NULL);
	}
	obj->vertices = NULL;
	while (get_next_line(fd, &cmd->to_parse) > 0)
	{
		cmd->get(cmd)->exec(cmd, obj);
	}
	cmd->destroy(&cmd);
	close(fd);
	return (obj);
}

void	ft_delete_content(void *content, size_t size)
{
	free(content);
}

void			ft_destroy_object(t_obj **obj)
{
	ft_lstdel(&(*obj)->vertices, ft_delete_content);
	ft_memdel((void **)&(*obj));
}

int main(int argc, char **argv)
{
	t_obj	*obj;
	char	*obj_name;
	char	*full_path;

	if (argc < 2)
		return (0);
	obj_name = argv[1];
	full_path = ft_strjoin(MODELS_DIR, obj_name);
	if (!full_path || !(obj = ft_obj_from_file(full_path)))
	{
		free(full_path);
		perror("ft_obj_from_file()");
		return (0);
	}
	ft_memdel((void **)&full_path);
	ft_destroy_object(&obj);
	// ctnr.obj_lst = NULL;
	// ft_lstadd(&ctnr.obj_lst, obj); // add object to main list

	// ft_lstmap(ctnr.obj_lst, ); free objects
	return (0);
}
//gcc parser.c command.c parser.h -I../libft/include ../libft/libft.a -I../libgl/include/ ../libgl/libgl.a && ./a.out 42.obj