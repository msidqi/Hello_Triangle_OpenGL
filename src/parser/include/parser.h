/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 18:02:23 by msidqi            #+#    #+#             */
/*   Updated: 2020/10/29 17:14:12 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include "libft.h"
# include "libgl.h"
# define MODELS_DIR "../../models/"

/*
** IM_OFF,					// 0. Color on and Ambient off
** IM_ON,					// 1. Color on and Ambient on
** IM_HIGHTLIGHT,			// 2. Highlight on
** IM_REF_RT,				// 3. Reflection on and Ray trace on
** IM_TRANS_GLASS_RT,	// 4. Transparency: Glass on, Reflection: Ray trace on
** IM_REF_FRENSEL_RT,		// 5. Reflection: Fresnel on and Ray trace on
** 6. Transparency: Refraction on, Reflection: Fresnel off and Ray trace on
** IM_TRANS_REF_RT,
** // 7. Transparency: Refraction on, Reflection: Fresnel on and Ray trace on
** IM_TRANS_REF_FRENSEL_RT,
** IM_REF_RT_OFF,			// 8. Reflection on and Ray trace off
** IM_TRANS_GLASS_RT_OFF,// 9. Transparency: Glass on, Reflection: Ray trace off
** IM_SHADOW_INVIS_SURF,	// 10. Casts shadows onto invisible surfaces
*/

typedef enum		e_illumination_mode
{
	IM_OFF,
	IM_ON,
	IM_HIGHTLIGHT,
	IM_REF_RT,
	IM_TRANS_GLASS_RT,
	IM_REF_FRENSEL_RT,
	IM_TRANS_REF_RT,
	IM_TRANS_REF_FRENSEL_RT,
	IM_REF_RT_OFF,
	IM_TRANS_GLASS_RT_OFF,
	IM_SHADOW_INVIS_SURF,
}					t_illumination_mode;

typedef enum		e_command_code
{
	C_UNINITIALIZED = -1,
	C_SKIP = 0,
	C_GEOMETRIC_VERTEX,
	C_TEXTURE_COORD,
	C_VERTEX_INDEX,
	C_COMMENT,
}					t_command_code;

/*
** flags to check what the face struct contains
*/

typedef enum		e_face_flags
{
	F_INDEX = 1,
	F_NORMAL = 2,
	F_TEXTURE_INDEX = 4
}					t_face_flags;

typedef struct		s_container
{
	t_list			*obj_lst;
}					t_container;

typedef struct		s_obj
{
	unsigned int	flags;
	char			*mtlib;
	t_list			*vertices;
	unsigned int	vertices_len;
	t_list			*tex_coords;
	unsigned int	tex_len;
	t_list			*indices;
	unsigned int	indices_len;
	t_list			*materials;
	float			*vertices_array;
	unsigned int	*vindices_array;
}					t_obj;

/*
**  flags F_INDEX | F_NORMAL | F_TEXTURE_INDEX
*/

typedef struct		s_face
{
	unsigned int	n_of_indices;
	unsigned int	flags;
	unsigned int	*vindices;
	unsigned int	*vnormals;
	unsigned int	*vtexture;
}					t_face;

typedef	struct	s_char2d
{
	char			**lines;
	unsigned int	length;
}				t_char2d;

/*
** char	*usemtl; // material name (defined in .mtl files by using "newmtl name")
** t_vec3f			ka; 	// ambient 0.0 to 1.0
** t_vec3f			kd; 	// diffuse 0.0 to 1.0
** t_vec3f			ks; 	// specular 0.0 to 1.0
** float			ns;		// specular exponent 0 to 1000
** float			ni; 	// index of refraction  0.001 to 10
** float			d;		// transparency 0.0 to 1.0
** float			illum;	// illumination mode | enum: t_illumination_mode
*/

typedef struct		s_material
{
	char			*usemtl;
	t_vec3f			ka;
	t_vec3f			kd;
	t_vec3f			ks;
	float			ns;
	float			ni;
	float			d;
	float			illum;
}					t_material;

typedef struct		s_cmd
{
	int				cmd_code;
	char			*to_parse;
	struct s_cmd	*(*get)(struct s_cmd *this);
	int				(*exec)(struct s_cmd *this, t_obj *obj);
	void			(*destroy)(struct s_cmd **this);
	unsigned int	(*parse_geometric_vertex)(char *line,
						t_list **vertices_lst);
	unsigned int	(*parse_texture_coords)(char *line,
						t_list **tex_coords);
	unsigned int	(*parse_indices)(char *line,
						t_list **indices_lst, unsigned int *indices_len);
}					t_cmd;

t_cmd				*ft_command_construct();

void				ft_print_vertices(t_obj *obj);
void				ft_print_indices(t_obj *obj);
void				ft_print_vertices_array(t_obj *obj);
void				ft_print_vindices_array(t_obj *obj,
										unsigned int *vindices_array);

/*
** object functions
*/

t_obj				*ft_obj_from_args(int argc, char **argv);
t_obj				*ft_obj_from_file(char *path);
int					ft_convert_object(t_obj *obj);
void				ft_destroy_object(t_obj **obj);
void				ft_delete_face(void *content, size_t size);
void				ft_delete_content(void *content, size_t size);

/*
** parsing functions
*/

unsigned int		ft_parse_indices(char *line,
								t_list **indices, unsigned int *indices_len);
unsigned int		ft_parse_geometric_vertex(char *line,
								t_list **vertices);
unsigned int		ft_parse_texture_coordinates(char *line,
								t_list **tex_coords);

/*
** face functions
*/

void				ft_destroy_face(t_face **face);
void			ft_store_face_components(t_face *face,
								unsigned int i, unsigned int values[3]);
int					ft_allocate_face_components(t_face *face);
t_face				*new_face(unsigned int flags, unsigned int n_of_indices);

#endif
