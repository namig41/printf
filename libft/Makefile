# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/27 15:54:57 by lcarmelo          #+#    #+#              #
#    Updated: 2020/02/05 15:00:42 by lcarmelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
		
FUN_CONVERSION = \
        ft_atoi \
		ft_lltoa \
		ft_uitoa_base \
		ft_ulltoa_base \

FUN_MEMORY = \
        ft_memset \
        ft_bzero \
        ft_memcpy \
        ft_memccpy \
        ft_memmove \
        ft_memchr \
        ft_memalloc \
        ft_memdel

FUN_STRINGS = \
        ft_isprint \
        ft_isdigit \
        ft_putchar \
        ft_putstr \
        ft_strlen \
        ft_strchr \
        ft_strchri 

DIR_CONVERSION  = ./conversion/
DIR_MEMORY      = ./memory/
DIR_STRINGS     = ./strings/

SRC_CONVERSION  = $(addprefix $(DIR_CONVERSION), $(addsuffix .c, $(FUN_CONVERSION)))
SRC_MEMORY      = $(addprefix $(DIR_MEMORY), $(addsuffix .c, $(FUN_MEMORY)))
SRC_STRINGS     = $(addprefix $(DIR_STRINGS), $(addsuffix .c, $(FUN_STRINGS)))

SRC_ALL         = $(SRC_CONVERSION) $(SRC_MEMORY) $(SRC_STRINGS) 
OBJ_ALL            = $(addsuffix .o, $(FUN_CONVERSION) $(FUN_MEMORY) $(FUN_STRINGS))

NAME            = libft.a
CC              = gcc
INCLUDE_PATH    = ./includes
CFLAGS          = -Wall -Wextra -Werror -I$(INCLUDE_PATH)

all: $(NAME)

$(OBJ_ALL):
	$(CC) -c $(CFLAGS) $(SRC_ALL) 

$(NAME): $(OBJ_ALL)
	@ar rc $(NAME) $?
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ_ALL)

fclean: clean
	@rm -f $(NAME)

re: fclean all
