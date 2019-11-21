# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/27 15:54:57 by lcarmelo          #+#    #+#              #
#    Updated: 2019/09/27 15:55:04 by lcarmelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf.a

SRC_DIR = ./src/
INC_DIR = ./includes/
LIB_DIR = ./libft/

SRC_NAME = ft_printf \

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_NAME)))
OBJS = $(addsuffix .o, $(SRC_NAME))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR) -I$(LIB_DIR)

all: $(NAME)

$(NAME): obj
	ar rc $(NAME) $(OBJS)
	ranlib $(NAME)

obj:
	$(CC) $(CFLAGS) -c $(SRCS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all