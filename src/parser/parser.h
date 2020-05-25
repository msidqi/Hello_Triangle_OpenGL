#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"
#include "libgl.h"
#define MODELS_DIR "../../models/"

typedef enum	e_illumination_mode
{
	IM_OFF,					// 0. Color on and Ambient off
	IM_ON,					// 1. Color on and Ambient on
	IM_HIGHTLIGHT,			// 2. Highlight on
	IM_REF_RT,				// 3. Reflection on and Ray trace on
	IM_TRANS_GLASS_RT,		// 4. Transparency: Glass on, Reflection: Ray trace on
	IM_REF_FRENSEL_RT,		// 5. Reflection: Fresnel on and Ray trace on
	IM_TRANS_REF_RT,		// 6. Transparency: Refraction on, Reflection: Fresnel off and Ray trace on
	IM_TRANS_REF_FRENSEL_RT,// 7. Transparency: Refraction on, Reflection: Fresnel on and Ray trace on
	IM_REF_RT_OFF,			// 8. Reflection on and Ray trace off
	IM_TRANS_GLASS_RT_OFF,	// 9. Transparency: Glass on, Reflection: Ray trace off
	IM_SHADOW_INVIS_SURF,	// 10. Casts shadows onto invisible surfaces
}				t_illumination_mode;

typedef enum	e_command_code
{
	C_UNINITIALIZED = -1,
	C_SKIP = 0,
	C_GEOMETRIC_VERTEX,
	C_VERTEX_INDEX,
	C_COMMENT,
}				t_command_code;

typedef struct	s_container
{
	t_list		*obj_lst;
}				t_container;

typedef struct	s_obj
{
	char		*mtlib; // name of .mtl file that contains color && texture of model
	t_list		*vertices;
	t_list		*indices;
	t_list		*materials;
}				t_obj;

typedef struct	s_material
{
	char		*usemtl; // material name (defined in .mtl files by using "newmtl name")
	t_vec3f		ka; 	// ambient 0.0 to 1.0
	t_vec3f		kd; 	// diffuse 0.0 to 1.0
	t_vec3f		ks; 	// specular 0.0 to 1.0
	float		ns;		// specular exponent 0 to 1000
	float		ni; 	// index of refraction  0.001 to 10
	float		d;		// transparency 0.0 to 1.0
	float		illum;	// illumination mode | enum: t_illumination_mode
}				t_material;

typedef struct	s_poly3
{
	t_vec3f		vertex0;
	t_vec3f		vertex1;
	t_vec3f		vertex2;
	t_vec3f		vertices[3];
}				t_poly3;

typedef struct	s_cmd_handler
{
	int						cmd_code;
	char					*to_parse;
	struct s_cmd_handler	*(*get)(struct s_cmd_handler *this); // expects this->to_parse to contain a string;
	int						(*exec)(struct s_cmd_handler *this, t_obj *obj);
	void					(*destroy)(struct s_cmd_handler *this);
	void					(*parse_geometric_vertex)(char *line, t_list **vertices_lst);
	void					(*parse_vertex_index)(char *line, t_list **indices_lst);
}				t_cmd_handler;

t_cmd_handler	*ft_command_construct();