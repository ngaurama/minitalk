NAME_SERVER = server
NAME_CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror

OBJ_DIR = obj

SRC_SERVER = server.c

SRC_CLIENT = client.c
OBJ_SERVER = $(SRC_SERVER:%.c=$(OBJ_DIR)/%.o)
OBJ_CLIENT = $(SRC_CLIENT:%.c=$(OBJ_DIR)/%.o)

LIBFT = libft/libft.a

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(LIBFT) $(NAME_SERVER) $(NAME_CLIENT)

$(NAME_SERVER): $(OBJ_SERVER) $(LIBFT)
	@echo "Linking $(NAME_SERVER)..."
	@$(CC) $(CFLAGS) $^ -o $@

$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT)
	@echo "Linking $(NAME_CLIENT)..."
	@$(CC) $(CFLAGS) $^ -o $@

bonus: all

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@echo "Building libft.."
	@make -C libft --no-print-directory

clean:
	@echo "Cleaning project files..."
	@rm -rf $(OBJ_DIR)
	@make -C libft clean --no-print-directory

fclean: clean
	@echo "Removing $(NAME_SERVER) and $(NAME_CLIENT)..."
	@rm -f $(NAME_SERVER) $(NAME_CLIENT)
	@make -C libft fclean --no-print-directory

re: fclean all

.PHONY: all clean fclean re bonus