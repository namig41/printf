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

NAME = ft_printf 

SRC_DIR = ./src/
INC_DIR = ./includes/
LIB_DIR = ./libft/

SRC_NAME = main \
			parse \

LIB_NAME = libft

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_NAME)))
OBJS = $(addsuffix .o, $(SRC_NAME))
LIBS = $(addprefix $(LIB_DIR), $(addsuffix .a, $(LIB_NAME)))

CC = gcc
CFLAGS = -I$(INC_DIR) -I$(LIB_DIR)

all: $(NAME)

obj:
	$(CC) $(CFLAGS) -c $(SRCS)

$(NAME): lib obj
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

lib:
	make -C $(LIB_DIR)

clean:
	make fclean -C $(LIB_DIR)
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all