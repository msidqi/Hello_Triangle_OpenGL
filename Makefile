NAME = exec
FLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm
LIBGLFW = /usr/lib/x86_64-linux-gnu/libglfw.so.3
LIBOPENGL = /usr/lib/x86_64-linux-gnu/libGL.so
LIBGL_H_PATH = src/libgl/include
LIBGL = src/libgl/libgl.a
PARSER_H_PATH = src/parser/include
PARSER = src/parser/src/*.c
LIBFT_H_PATH = src/libft/include
LIBFT = src/libft/src/*.c
SRC_FILES = main.c glad.c shaders/shader.c textures/texture_helper.c
SRC_PATH = src
OBJ_PATH = .obj
SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_FILES:.c=.o))
HEADERS = scop.h
HEADERSPATH = include

# ----- main
all : $(NAME)
$(NAME) : makelibgl makelibft
	gcc -o $(NAME) $(SRC) $(LIBGL) src/libgl/src/ft_atof.c $(LIBFT) $(PARSER) -I$(HEADERSPATH) -I$(LIBGL_H_PATH) -I$(PARSER_H_PATH) -I$(LIBFT_H_PATH) $(FLAGS)

clean : cleanlibgl cleanlibft cleanparser
	rm -rf $(NAME)
fclean : clean cleanlibgl cleanlibft cleanparser
	rm -rf $(NAME)
re : fclean all

# ----- parser
makeparser:
	make -C src/parser
cleanparser:
	make fclean -C src/parser

# ----- libgl
makelibgl:
	make -C src/libgl
cleanlibgl:
	make fclean -C src/libgl

# ----- libft
makelibft:
	make -C src/libft
cleanlibft:
	make fclean -C src/libft
