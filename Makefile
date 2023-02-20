# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/24 15:53:01 by tbelleng          #+#    #+#              #
#    Updated: 2023/02/20 13:17:47 by tbelleng         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_BONUS = pipex_bonus

SRC_DIR = ./src

SRC_BONUS_DIR = ./bonus

BIN_DIR = ./bin/

SRC =	$(SRC_DIR)/pipex.c     \
		$(SRC_DIR)/error.c     \
		$(SRC_DIR)/command_exe.c   \


SRC_BONUS =  $(SRC_BONUS_DIR)/pipex_bonus.c      \
			 $(SRC_BONUS_DIR)/error_bonus.c      \
			 $(SRC_BONUS_DIR)/here_doc.c      \
			 $(SRC_BONUS_DIR)/command_exe_bonus.c      \
			 $(SRC_BONUS_DIR)/gnl.c      \
			 $(SRC_BONUS_DIR)/gnl_utils.c      \
			 $(SRC_BONUS_DIR)/outfile.c      \


OBJ = $(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)%.o)

OBJ_BONUS = $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(BIN_DIR)/%.o)

LIB_PATH = ./libft

LIB = -Llibft -lft

INCLUDES = ./includes

CFLAGS = -Wall -Werror -Wextra -I$(INCLUDES) -g3

all :	$(BIN_DIR) $(NAME)

bonus:	$(NAME_BONUS)

$(OBJ) :	 $(BIN_DIR)%.o: $(SRC_DIR)/%.c
		@ $(CC) -I$(INCLUDES) -c $< -o $@
		
$(OBJ_BONUS) :	 $(BIN_DIR)/%.o: $(SRC_BONUS_DIR)/%.c $(BIN_DIR)
		@ $(CC) $(CFLAGS) -c $< -o $@

$(NAME) :	$(BIN_DIR) $(OBJ)
			@ $(MAKE) -s -C $(LIB_PATH)
			@ $(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)
			@ echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mDone ! ✅"
			
$(NAME_BONUS) :	$(BIN_DIR) $(OBJ_BONUS)
			@ $(MAKE) -s -C $(LIB_PATH)
			@ $(CC) $(CFLAGS) $(OBJ_BONUS) $(LIB) -o $(NAME_BONUS)
			@ echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mDone ! ✅"

$(BIN_DIR) :
		@ mkdir -p $(BIN_DIR)

clean :
		@ $(MAKE) -s clean -C $(LIB_PATH)
		@ rm -f $(OBJ)
		@ rm -f $(OBJ_BONUS)
		@ rm -rf $(BIN_DIR)
		@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove binary files .. 🧹"

fclean : clean
		@ $(MAKE) -s fclean -C $(LIB_PATH)
		@ rm -f $(NAME)
		@ rm -f $(NAME_BONUS)
		@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRemove executable .. 🗑️"
		
re :
	@echo "\e[33m\e[1m\tMake\e[0m [🗿] : \e[1mRecompile .. 🔄"
	@ $(MAKE) -s fclean all

.PHONY: all $(SRC_BONUS_DIR) clean fclean re