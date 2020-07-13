/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 12:50:19 by msidqi            #+#    #+#             */
/*   Updated: 2020/07/13 10:19:59 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_obj			*ft_obj_from_file(char *path)
{
	int		fd;
	t_cmd	*cmd;
	t_obj 	*obj;

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
		cmd->get(cmd)->exec(cmd, obj);
	cmd->destroy(&cmd);
	close(fd);
	return (obj);
}

void		ft_delete_content(void *content, size_t size)
{
	free(content);
	(void)size;
}

void		ft_delete_face(void *content, size_t size)
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
	if ((*obj)->vertices)
		ft_lstdel(&(*obj)->vertices, ft_delete_content);
	if ((*obj)->indices)
		ft_lstdel(&(*obj)->indices, ft_delete_face);
	if ((*obj)->vindices_array)
		ft_memdel((void **)&(*obj)->vindices_array);
	if ((*obj)->vertices_array)
		ft_memdel((void **)&(*obj)->vertices_array);
	ft_memdel((void **)&(*obj));
}

t_obj			*ft_obj_from_args(int argc, char **argv)
{
	t_obj	*obj;
	char	*full_path;
	if (argc < 2)
	{
		ft_putendl_fd("Usage: ./scop [filename] [texture]", 2);
		return (NULL);
	}
	full_path = argv[1];
	ft_putendl_fd("reading file...", 1);
	if (!full_path || !(obj = ft_obj_from_file(full_path)))
	{
		perror("ft_obj_from_file()");
		return (NULL);
	}
	ft_putendl_fd("reading file done.", 1);
	return (obj);
}
