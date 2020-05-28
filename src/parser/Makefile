NAME = parser.a
LIBGL_H_PATH = ../libgl/include
LIBFT_H_PATH = ../libft/include
LIBGL = ../libgl/libgl.a
LIBFT = ../libft/libft.a
SRC_PATH = src
SRC = command.c  parser.c  print.c
OBJS_DIR = .obj
# SRC = $(addprefix $(SRC_PATH)/, $(SRC_FILES))
OBJ = $(addprefix $(OBJS_DIR)/,$(SRC:.c=.o))
HEADERS = parser.h
HEADERSPATH = include

# ----- main
all : $(NAME)

$(OBJ) : $(OBJS_DIR)/%.o : $(SRC_PATH)/%.c | $(OBJS_DIR) makelibgl makelibft
	$(CC) -c $^ -o $@ -I$(HEADERSPATH) -I$(LIBGL_H_PATH) -I$(LIBFT_H_PATH)

$(NAME) : $(OBJ)
	ar rc $@ $(OBJ)
	ranlib $(NAME)
# $(NAME) : $(OBJ) makelibgl makelibft
# 	gcc -o $(NAME) $(SRC) $(LIBFT) $(LIBGL) -I$(HEADERSPATH) -I$(LIBGL_H_PATH) -I$(LIBFT_H_PATH)

clean : cleanlibgl cleanlibft
	rm -rf $(OBJ)
fclean : clean cleanlibgl cleanlibft
	rm -rf $(NAME)
re : cleanlibgl cleanlibft fclean all

# ----- libft
makelibft:
	make -C ../libft
cleanlibft:
	make fclean -C ../libft


# ----- libgl
makelibgl:
	make -C ../libgl
cleanlibgl:
	make fclean -C ../libgl

$(OBJS_DIR):
	mkdir $(OBJS_DIR)
