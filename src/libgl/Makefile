# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msidqi <msidqi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/23 00:08:25 by msidqi            #+#    #+#              #
#    Updated: 2020/06/06 11:24:22 by msidqi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBGL = libgl.a
LIBGLL = libgl.a
SRC_PATH = src
SRC = ft_solve_equation_3.c ft_vec_scalar.c ft_angle_radian.c\
ft_filters.c  ft_solve_equation_4.c ft_vector_add.c \
ft_utils_func.c ft_vector_operations.c \
ft_atof.c ft_min_max.c ft_vec_create.c ft_vector_sub.c \
ft_multi_thread.c ft_vec_cross_dot_prod.c \
ft_color_operations.c ft_mat_create_destroy.c\
ft_screenshot.c ft_vec_normalize_magnitude.c ft_put_vectors.c \
ft_rotate_vector.c strings.c ft_matrix_transform.c ft_matrix.c \
ft_matrix_create.c ft_matrix_op.c ft_matrix_perspective.c\
ft_matrix_transform_f.c ft_matrix_op_f.c ft_putmat4.c
# ft_gl_mat_transform.c ft_gl_mat_create.c ft_gl_mat.c
INCLUDE = include
INC = include/libgl.h
OBJS_DIR = .objs
CC = gcc -Wall -Wextra -Werror
OBJ = $(addprefix $(OBJS_DIR)/,$(SRC:.c=.o))

all : $(LIBGLL)

$(OBJ) : $(OBJS_DIR)/%.o : $(SRC_PATH)/%.c $(INC) | $(OBJS_DIR)
	$(CC) -c $< -o $@ -I$(INCLUDE)
$(LIBGLL) : $(OBJ)
	ar rc $@ $^
	ranlib $@

clean :
	rm -rf $(OBJ) $(LIBGLL)
fclean : clean
	rm -rf $(NAME)
re : fclean all

$(OBJS_DIR):
	mkdir $(OBJS_DIR)
