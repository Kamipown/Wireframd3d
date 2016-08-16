#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdelobbe <pdelobbe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/24 16:27:28 by pdelobbe          #+#    #+#              #
#    Updated: 2015/04/29 17:26:11 by pdelobbe         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME =	fdf

FLG =	-Wall -Wextra -Werror

SRC =	main.c \
		init.c \
		hooks.c \
		parser.c \
		get_next_line.c \
		drawer.c \
		translations.c \
		rotations.c \
		scale.c \
		color.c

OBJ =	$(SRC:.c=.o)

all: $(NAME)

$(NAME):
	make -C libft/
	make -C minilibx_macos/
	gcc -O3 $(FLG) -I libft/includes/ -c $(SRC)
	gcc -o $(NAME) $(OBJ) -L./libft/ -lft -L./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
