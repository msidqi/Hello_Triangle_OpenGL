NAME = exec
FLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm
# FLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
LIBGLFW = /usr/lib/x86_64-linux-gnu/libglfw.so.3
LIBOPENGL = /usr/lib/x86_64-linux-gnu/libGL.so
LIBGL_H_PATH = src/libgl/include
LIBGL = src/libgl/libgl.a
SRC_FILES = main.c glad.c shaders/shader.c textures/texture_helper.c
SRC_PATH = src
OBJ_PATH = .obj
SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_FILES:.c=.o))
HEADERS = scop.h
HEADERSPATH = include
# INCLUDE = $(addprefix include/, $(HEADERS))

# ----- main
all : $(NAME)
$(NAME) : makelibgl
	gcc -o $(NAME) $(SRC) $(LIBGL) -I$(HEADERSPATH) -I$(LIBGL_H_PATH) $(FLAGS)
	# gcc -E $(SRC) $(HEADERSPATH)/scop.h $(FLAGS)
	# gcc -o $(NAME) $(SRC) -I$(HEADERSPATH) $(FLAGS)

clean : cleanlibgl
	rm -rf $(NAME)
fclean : clean cleanlibgl
	rm -rf $(NAME)
re : cleanlibgl fclean all

# ----- libgl
makelibgl:
	make -C src/libgl
cleanlibgl:
	make fclean -C src/libgl
