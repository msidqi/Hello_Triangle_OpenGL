/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 21:43:22 by msidqi            #+#    #+#             */
/*   Updated: 2020/06/06 14:39:10 by msidqi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGL_H
# define LIBGL_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <pthread.h>
# include <time.h>
# include <stdio.h>
# include <fcntl.h>

# define ABS(Value) (Value >= 0) ? (Value) : -(Value)
# define STATIC_ARRAY_SIZE(ptr) (sizeof(ptr) / sizeof(ptr[0]))
# define MAX_ITER 30
# define VERTEX 0
# define VECTOR 1
# define DIRECTION 2
# define MATRIX 3
# define TRANSLATION_MATRIX 0
# define ROTATION_MATRIX 1
# define SCALING_MATRIX 2
# define NEAR 1e-6
# define FAR 1e+6
# define MICRO 1e-6
# define MEGA 1e+6
# define DISTANT_LIGHT 1e+6
# define RED 0xFF0000
# define GREEN 0xFF00
# define BLUE 0xFF
# define BLACK 0x0
# define WHITE 0xFFFFFF
# define ASPECT_RATIO HEIGHT / WIDTH
# define PI 3.14159265358979323846
# define N_THREADS 4

typedef enum		e_event_code
{
	MOUSE_PRESS_CODE = 4,
	MOUSE_MOVE_CODE = 6,
	KEY_PRESS_CODE = 2,
	KEY_RELEASE_CODE = 3,
	RED_BUTTON_CODE = 17,
}					t_event_code;

typedef enum		e_ft_mlx_hooks
{
	NO_EVENT_HOOK = 0,
	MOUSE_PRESS_HOOK = 1,
	MOUSE_MOVE_HOOK = 2,
	KEY_PRESS_HOOK = 4,
	RED_BUTTON_HOOK = 8,
}					t_ft_mlx_hooks;

typedef enum		e_key_code
{
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	SCROLL_UP = 4,
	SCROLL_DOWN = 5,
	ZOOM_IN = 69,
	ZOOM_OUT = 78,
	SPACE = 49,
	NUM_LOCK_9 = 92,
	NUM_LOCK_8 = 91,
	NUM_LOCK_7 = 89,
	NUM_LOCK_6 = 88,
	NUM_LOCK_5 = 87,
	NUM_LOCK_4 = 86,
	NUM_LOCK_3 = 85,
	NUM_LOCK_2 = 84,
	NUM_LOCK_1 = 83,
	NUM_LOCK_0 = 82,
	RIGHT_ARROW = 124,
	LEFT_ARROW = 123,
	UP_ARROW = 126,
	DOWN_ARROW = 125,
}					t_key_code;

typedef struct		s_vec2
{
	double			x;
	int				y;
}					t_vec2;

typedef struct		s_vec2i
{
	int				x;
	int				y;
}					t_vec2i;

typedef struct		s_vec2f
{
	float			x;
	float			y;
}					t_vec2f;

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_col
{
	double			r;
	double			g;
	double			b;
}					t_col;	

typedef struct		s_vec3f
{
	float			x;
	float			y;
	float			z;
}					t_vec3f;

typedef struct		s_vec3i
{
	int				x;
	int				y;
	int				z;
}					t_vec3i;

typedef union		u_vec3
{
    struct { float x, y, z; };
    struct { float r, g, b; };
    float arr[3];
}					tu_vec3;

typedef struct		s_matrix
{
	int				cols;
	int				rows;
	double			**v;
}					t_matrix;

typedef struct		s_vec4
{
	double			x;
	double			y;
	double			z;
	double			w;
}					t_vec4;

typedef struct		s_vec4f
{
	float			x;
	float			y;
	float			z;
	float			w;
}					t_vec4f;

/*
** Homogenous Coordinates
**   F U R  T   (Forward/Up/Right/Translation Vector)
** [[1 0 0] 0]
** [[0 1 0] 0]
** [[0 0 1] 0]
** [ 0 0 0  1] 0 Direction Vector 1 Position Vector
** FUR == unit vectors describing object orientation. aka vector basis
*/

union mat4 {
	struct			s_m
	{
		double		x0;
		double		x1;
		double		x2;
		double		x3;
		double		y0;
		double		y1;
		double		y2;
		double		y3;
		double		z0;
		double		z1;
		double		z2;
		double		z3;
		double		w0;
		double		w1;
		double		w2;
		double		w3;
	}				t_m;
	double			v[4][4];
	// float			f[4][4];
};

typedef struct		s_mat4
{
	double			v[4][4];
}					t_mat4;

typedef struct		s_mat4f
{
	float			v[4][4];
}					t_mat4f;

typedef struct		s_startend
{
	t_vec2			start;
	t_vec2			end;
}					t_startend;

typedef struct		s_color
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
}					t_color;

typedef enum		e_bool
{
	false, true
}					t_bool;

/*
** P(t) = origin + t * dir
** t_vec4 origin : vector to origin point
** t_vec4 dir : direction vector
** t_vec4 t : distance
*/

/*
** r : intensity rgb(1.0, 0.0, 0.0) == red
** 	t_vec4	dir: direcional light && spot light
** 	t_vec4	u_dir: area light orientation vectors
** 	float	spot_dot: angle of the spot light ]-1, 0[
** 	unsigned short	u_nodes: number of nodes in area light
*/

typedef	struct		s_data
{
	int				max_iter;
	double			filter;
	t_color			color;
	t_startend		thread_range;
	int				winwidth;
	int				winheight;
	void			*mlx;
	void			*win;
	void			*img_ptr;
	int				*image;
	int				endian;
	int				size_line;
	int				bpp;
}					t_data;

typedef struct		s_obj_function
{
	size_t			type;
	int				(*call)();
	int				(*call2)();
}					t_obj_function;

double				ft_to_rad(double deg);
double				ft_to_deg(double radian);
float				ft_to_radf(float deg);
float				ft_to_degf(float radian);
double				lerp(double x1, double x2, double lerp);
t_vec2				ft_vec2_lerp(t_vec2 v1, t_vec2 v2, double lrp);
double				ft_lerp(double goal, double current, double delta_time);
double				ft_get_world_pos(double screen_coord,
								double widthheight, double zoom);
void				ft_multi_thread(t_data *data, void *(*f)(void *));
void				ft_create_vec2(t_vec2 *a, double x, double y);
void				ft_create_vec3(t_vec3 *a, double x, double y, double z);
t_vec2				ft_vec2_add(t_vec2 a, t_vec2 b);
t_vec3				ft_vec3_add(t_vec3 a, t_vec3 b);
t_vec2				ft_vec2_sub(t_vec2 a, t_vec2 b);
t_vec3				ft_vec3_sub(t_vec3 a, t_vec3 b);
t_vec2				ft_vec2_scalar(t_vec2 a, double factor);
t_vec3				ft_vec3_scalar(t_vec3 a, double factor);
double				ft_vec2_mag(t_vec2 a);
double				ft_vec3_mag(t_vec3 a);
double				ft_vec2_mag_cmp(t_vec2 a, t_vec2 b);
double				ft_vec3_mag_cmp(t_vec3 a, t_vec3 b);
t_vec2				ft_vec2_normalize(t_vec2 a);
t_vec3				ft_vec3_normalize(t_vec3 a);
double				ft_vec2_dot_product(t_vec2 a, t_vec2 b);
double				ft_vec3_dot_product(t_vec3 a, t_vec3 b);
t_vec2				ft_vec2_rotate_byangle(t_vec2 a, double angle);
t_vec2				ft_vec2_rotate_byaxis(t_vec2 a, t_vec2 x_axis,
		t_vec2 y_axis);
t_vec3				ft_vec3_rotate_z(t_vec3 vector, double rotation_angle);
t_vec3				ft_vec3_rotate_y(t_vec3 vector, double rotation_angle);
t_vec3				ft_vec3_rotate_x(t_vec3 vector, double rotation_angle);
t_vec2				ft_vec2_from_angle(double size, double angle);
t_matrix			*ft_create_matrix(int rows, int cols);
t_mat4				ft_mat4_create();
t_mat4				ft_mat4_create_init(double init);

t_mat4f				ft_mat4f_create(void);
t_mat4f				ft_mat4f_create_init(float init);
t_vec4f				ft_mat4f_x_vec4f(t_mat4f m, t_vec4f v);
t_vec4f				ft_mat4f_x_vec4f_col(t_mat4f m, t_vec4f v);
t_mat4f				ft_mat4f_x_mat4f(t_mat4f m0, t_mat4f m1);
t_mat4f				ft_mat4f_x_mat4f_col(t_mat4f m0, t_mat4f m1);
t_mat4f				ft_mat4f_scale_f(t_mat4f mat, float x, float y, float z);
t_mat4f				ft_mat4f_scale(t_mat4f mat, t_vec3f v);
t_mat4f				ft_mat4f_translate_f(t_mat4f mat, float x, float y, float z);
t_mat4f				ft_mat4f_translate(t_mat4f mat, t_vec3f v);
t_mat4f				ft_mat4f_translate_row(t_mat4f mat, t_vec3f v);
t_mat4f				ft_mat4f_rotation_x(float angle_rad);
t_mat4f				ft_mat4f_rotation_y(float angle_rad);
t_mat4f				ft_mat4f_rotation_z(float angle_rad);
t_mat4f				ft_mat4f_rotation_xyz(float angle_rad, t_vec3f v);
t_mat4f				ft_mat4f_rotate(t_mat4f mat, float angle_rad, t_vec3f v);
t_mat4f				ft_perspective_matrixf(float fov_rad, float asp_ratio, float near, float far);
t_mat4f				ft_perspective_matrixf_row(float fov_rad, float asp_ratio, float near, float far);
int					ft_destroy_matrix(t_matrix *mat);
t_mat4				ft_get_translation_matrix4(t_mat4 mat, double x,
		double y, double z);
t_mat4				ft_mat4_scale_d(t_mat4 mat, double x, double y,
		double z);
t_mat4				ft_mat4_scale(t_mat4 mat, t_vec3 v);
t_mat4				ft_mat4_translate_d(t_mat4 mat, double x, double y, double z);
t_mat4				ft_mat4_translate(t_mat4 mat, t_vec3 v);
t_mat4				ft_mat4_translate_row(t_mat4 mat, t_vec3 v);
t_mat4				ft_mat4_rotate(t_mat4 mat, double angle, t_vec3 vec);
t_mat4				ft_mat4_rotation_x(double angle_rad);
t_mat4				ft_mat4_rotation_y(double angle_rad);
t_mat4				ft_mat4_rotation_z(double angle_rad);
t_mat4				ft_mat4_rotation_xyz(double angle_rad, t_vec3 v);
t_vec4				ft_create_vec4(double x, double y, double z, double w);
t_mat4				ft_mat4_x_mat4(t_mat4 m0, t_mat4 m1);
t_mat4				ft_mat4_x_mat4_col(t_mat4 m0, t_mat4 m1);
t_vec4				ft_mat4_x_vec4(t_mat4 mat, t_vec4 vec);
t_vec4				ft_mat4_x_vec4_col(t_mat4 mat, t_vec4 vec);
t_mat4				ft_perspective_matrix(float fov_rad, float asp_ratio, float near, float far);

void				ft_putvec3(t_vec3 *vec);
void				ft_putvec4(t_vec4 *vec);
void				ft_putmat4(t_mat4 *mat);
void				ft_putmat4f(t_mat4f *mat);
t_vec4				ft_vec4_sub(t_vec4 vec1, t_vec4 vec2);
t_vec4				ft_vec4_normalize(t_vec4 a);
double				ft_vec4_mag(t_vec4 a);
double				ft_vec4_dot_product(t_vec4 a, t_vec4 b);
t_vec3				ft_vec3_cross_product(t_vec3 vec1, t_vec3 vec2);
t_vec4				ft_vec4_cross_product(t_vec4 vec1, t_vec4 vec2);
t_vec4				ft_vec4_add(t_vec4 vec1, t_vec4 vec2);
t_vec4				ft_vec4_scalar(t_vec4 a, double factor);

int					ft_color_rgb_scalar(int color, double r, double g,
		double b);
int					ft_color_add(int color1, int color2);
int					ft_color_avg(int *colors, int size);

double				ft_min(double val, double min);
double				ft_max(double val, double max);

void				ft_filters(t_data *data, int x, int y, int color);
int					ft_filters_aa(t_data *data, int color);

typedef struct		s_function
{
	char			*type;
	void			(*call)();
}					t_function;

size_t				ft_strlen(const char *str);
void				ft_putstr_fd(const char *s, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putnbr_fd(int nb, int fd);
void				ft_putnbr(int nb);

double				ft_atof(char *nbr);

void				*ft_screenshot(void *param);

typedef struct		s_solution
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
	double			m;
	double			n;
	double			q;
	double			p;
	double			o;
	double			tmp;
}					t_solve;

int					ft_solve_equation_4(t_solve s, double *x);
int					ft_solve_equation_3(double *x, double a, double b,
		double c);
void				ft_sort_double_table(double *x);

#endif
