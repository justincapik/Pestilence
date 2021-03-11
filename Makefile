# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: paulo <paulo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/06 16:34:32 by pharatyk          #+#    #+#              #
#    Updated: 2021/03/01 15:38:07 by paulo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 			Famine

OBJ_DIR  =		./obj/

SRC_DIR =	./src/
SRC_WWP = 	main.c\
		write64.c\
		write32.c\
		output_handle.c


SRCS      =	$(addprefix $(SRC_DIR), $(SRC_WWP))

OBJ  =	$(addprefix $(OBJ_DIR), $(SRC_WWP:.c=.o))

CC = gcc -g #-Wall -Wextra -Werror -Wuninitialized
CFLAGS  = -I ./inc/


all: $(NAME)

$(NAME): $(OBJ) $(ASM_OBJ)
	@$(CC) -o $(NAME) $(OBJ) 
	@printf " _/\nwoody  [done]\n"

lib:
	@make -C ./libft/

clean:
	@rm -f $(OBJ)
	@printf "clean  [done]\n"

fclean: clean
	@rm -f $(NAME)
	@printf "fclean [done]\n"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@printf ">"
	@$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

re: fclean all

.PHONY: all clean fclean re lib $(NAME) $(ASM_NAME)

