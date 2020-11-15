NAME = exec
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	FLAGS = -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lm
endif
ifeq ($(UNAME_S),Darwin)
	LIBGLFW_MACOS = ~/.brew/Cellar/glfw/3.3.2/lib/libglfw.dylib
	FLAGS = -framework OpenGL -lpthread -lm
	FLAGS += $(LIBGLFW_MACOS)
endif
COMPILER = gcc
COMPILER_FLAGS = -Wall -Wextra -Werror
LIBGLFW = /usr/lib/x86_64-linux-gnu/libglfw.so.3
LIBOPENGL = /usr/lib/x86_64-linux-gnu/libGL.so
LIBGL_H_PATH = src/libgl/include
LIBGL = src/libgl/libgl.a
PARSER_H_PATH = src/parser/include
PARSER = src/parser/parser.a
LIBFT_H_PATH = src/libft/include
LIBFT = src/libft/libft.a
SRC_FILES = main.c glad.c setup.c buffers.c events.c events_callbacks.c fps_counter.c texture_loader.c \
			shaders/shader.c shaders/init_shader.c shaders/shader_setuniforms0.c shaders/shader_setuniforms1.c \
			ft_model_world_view.c  textures/texture_helper.c textures/texture_construct.c handle_buffers.c \
			events_key_press.c
SRC_PATH = src
OBJ_PATH = .obj
SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH)/, $(SRC_FILES:.c=.o))
HEADERS = scop.h
HEADERSPATH = include

# ----- main
all : $(NAME)
$(NAME) : $(LIBFT) $(LIBGL) $(PARSER) $(OBJ)
	$(COMPILER) $(COMPILER_FLAGS) -o $(NAME) $(SRC) $(LIBGL) $(LIBFT) $(PARSER) -I$(HEADERSPATH) -I$(LIBFT_H_PATH) -I$(LIBGL_H_PATH) -I$(PARSER_H_PATH) $(FLAGS)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c | $(OBJ_PATH)
	$(CC) -c $< -o $@ -I$(HEADERSPATH) -I$(LIBFT_H_PATH) -I$(LIBGL_H_PATH) -I$(PARSER_H_PATH)

$(OBJ_PATH):
	mkdir $(OBJ_PATH) .obj/shaders .obj/textures

clean : cleanlibgl cleanlibft cleanparser
	rm -rf $(NAME)
fclean : clean cleanlibgl cleanlibft cleanparser
	rm -rf $(NAME)
re : fclean all

# ----- parser
$(PARSER):
	make -C src/parser
cleanparser:
	make fclean -C src/parser

# ----- libgl
$(LIBGL):
	make -C src/libgl
cleanlibgl:
	make fclean -C src/libgl

# ----- libft
$(LIBFT):
	make -C src/libft
cleanlibft:
	make fclean -C src/libft
