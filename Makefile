# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/27 15:54:57 by lcarmelo          #+#    #+#              #
#    Updated: 2020/02/07 18:36:11 by lcarmelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FUN_NAME = \
	ft_printf \
	handle_numbers \
	handle_strings \
	parse \
	print

DIR_SRC		= ./src/
DIR_INC		= ./includes/
DIR_LIB		= ./libft/

SRC_PRINTF 	= $(addprefix $(DIR_SRC), $(addsuffix .c, $(FUN_NAME)))
OBJ_PRINTF 	= $(addsuffix .o, $(FUN_NAME))

NAME 		= libftprintf.a
CC 	   	= gcc
CFLAGS 	   	= -Wall -Wextra -Werror -O2 -I$(DIR_INC) -I$(DIR_LIB)$(DIR_INC)

all: $(NAME)

$(NAME):
	@make -C $(DIR_LIB)
	@cp libft/libft.a ./$(NAME)
	@$(CC) -c $(CFLAGS) $(SRC_PRINTF)
	@ar rc $(NAME) $(OBJ_PRINTF)
	@ranlib $(NAME)

clean:
	@make clean -C $(DIR_LIB)
	@rm -f $(OBJ_PRINTF)

fclean: clean
	@make fclean -C $(DIR_LIB)
	@rm -f $(NAME)

re: fclean all

compile: all clean
	@$(CC) $(CFLAGS) src/main.c $(NAME)	

.PHONY: all clean fclean re compile
