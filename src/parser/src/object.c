#include "parser.h"

t_obj			*ft_obj_from_file(char *path)
{
	int				fd;
	t_cmd	*cmd;
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

static void		ft_delete_content(void *content, size_t size)
{
	free(content);
	(void)size;
}

static void		ft_delete_face(void *content, size_t size)
{
	t_face *face;
	
	face = (t_face *)content;
	free(face->vindices);
	free(face->vnormals);
	free(face->vtexture);
	free(face);
	(void)size;
}

void			ft_destroy_object(t_obj **obj)
{
	ft_lstdel(&(*obj)->vertices, ft_delete_content);
	ft_lstdel(&(*obj)->indices, ft_delete_face);
	ft_memdel((void **)&(*obj));
}

t_obj			*ft_obj_from_args(int argc, char **argv)
{
	t_obj	*obj;
	char	*full_path;
	if (argc < 2)
		return (NULL);
	full_path = argv[1];
	if (!full_path || !(obj = ft_obj_from_file(full_path)))
	{
		perror("ft_obj_from_file()");
		return (NULL);
	}
	return (obj);
}
