# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/27 15:54:57 by lcarmelo          #+#    #+#              #
#    Updated: 2020/02/05 15:05:32 by lcarmelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

SRC_DIR = ./src/
INC_DIR = ./includes/
LIB_DIR = ./libft/

FUN_NAME = \
            ft_printf \
            handle_numbers \
            handle_strings \
            parse \
            print

SRC_PRINTF = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_NAME)))
OBJ_PRINTF = $(addsuffix .o, $(SRC_NAME))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

all: $(NAME)

$(OBJ_PRINTF):
	$(CC) -c $(CFLAGS) $(SRC_PRINTF)

$(NAME): $(OBJ_PRINTF)
	ar rc $(NAME) $?
	ranlib $(NAME)
	rm -f $(OBJ_PRINTF)
    make -C $(LIB_DIR)

clean:
	rm -f $(OBJ_PRINTF)
    make clean -C $(LIB_DIR)

fclean: clean
	rm -f $(NAME)
    make fclean -C $(LIB_DIR)

re: fclean all
