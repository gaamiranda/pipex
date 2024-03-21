NAME = pipex
BONUS_NAME = pipex_bonus
CC = cc
CFLAGS = -I include -fsanitize=address
SRC = src/main.c src/split.c src/extra.c
BONUS_SRC = bonus/main.c bonus/split.c bonus/extra.c bonus/onemore.c
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

Color_Off = '\033[0m'
Red = '\033[0;91m'
Green = '\033[0;92m'
Yellow = '\033[0;93m'
Cyan = '\033[0;96m'

MSG1 = @echo $(Green)"$(NAME) compiled successfully"$(Color_Off)
MSG2 = @echo $(Cyan)"cleaned completely"$(Color_Off)
MSG3 = @echo $(Yellow)"$(NAME) cleaned"$(Color_Off)
MSG4 = @echo $(Red)"$(BONUS_NAME) compiled successfully"$(Color_Off)

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) -Imlx -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) $(INCLUDES) -o $(NAME)
	$(MSG1)

clean:
	@rm -rf $(OBJ_DIR)
	$(MSG3)

fclean: clean
	@rm -f $(NAME)
	rm -f $(BONUS_NAME)
	$(MSG2)

bonus:
	$(CC) $(CFLAGS) $(INCLUDES) $(BONUS_SRC) -o $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus