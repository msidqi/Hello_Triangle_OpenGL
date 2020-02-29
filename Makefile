NAME = ogl
FLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl 
# FLAGS = -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
LIBGLFW = /usr/lib/x86_64-linux-gnu/libglfw.so.3
LIBOPENGL = /usr/lib/x86_64-linux-gnu/libGL.so
SRC_FILES = main.c glad.c
SRC_PATH = src
OBJ_PATH = .obj
SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_FILES:.c=.o))
# HEADERS = glad/glad.h KHR/khrplatform.h
# INCLUDE = $(addprefix include/, $(HEADERS))

all : $(NAME)

$(NAME) :
	gcc -o $(NAME) $(SRC) $(FLAGS)

clean : 
	rm -rf ogl
fclean : clean
	rm -rf ogl
re : fclean all