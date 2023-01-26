# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 15:53:01 by tbelleng          #+#    #+#              #
#    Updated: 2023/01/26 17:21:27 by tbelleng         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC_DIR = ./src

BIN_DIR = ./bin/

SRC =	$(SRC_DIR)/pipex.c     \
		$(SRC_DIR)/command_exe.c   \

OBJ = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)%.o)

LIB_PATH = ./libft

LIB = -Llibft -lft

INCLUDES = ./includes

CFLAGS = -Wall -Werror -Wextra -I$(INCLUDES)

all :	$(BIN_DIR) $(NAME)

$(OBJ) :	 $(BIN_DIR)%.o: $(SRC_DIR)/%.c
		@ $(CC) -I$(INCLUDES) -c $< -o $@

$(NAME) :	$(BIN_DIR) $(OBJ)
			@ $(MAKE) -s -C $(LIB_PATH)
			@ $(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)
			@ echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mDone ! ✅"

$(BIN_DIR) :
		@ mkdir -p $(BIN_DIR)

clean :
		@ $(MAKE) -s clean -C $(LIB_PATH)
		@ rm -f $(OBJ)
		@ rm -rf $(BIN_DIR)
		@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove binary files .. 🧹"

fclean : clean
		@ $(MAKE) -s fclean -C $(LIB_PATH)
		@ rm -f $(NAME)
		@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove executable .. 🗑️"
		
re :
	@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRecompile .. 🔄"
	@ $(MAKE) -s fclean all

.PHONY: all clean fclean re