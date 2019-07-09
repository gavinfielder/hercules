# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfielder <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/28 21:19:45 by gfielder          #+#    #+#              #
#    Updated: 2019/05/18 15:25:51 by gfielder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=proxy
CC=clang
CFLAGS=-Wall -Wextra -Werror
INC=-I inc -I libft/inc
LIB=-L libft -lft
DEF=-D MY_IP_ADDRESS="\"$(ifconfig en0 | grep "broadcast" | cut -d ' ' -f 2)\""

SRC=src/main.c src/http.c src/iface.c src/serve.c src/s404.c \
	src/timer.c src/resolve.c src/proxy.c src/utils.c src/proxy_async.c

all: $(NAME)

$(NAME): $(SRC)
	@make -C libft/ > /dev/null
	@$(CC) $(CFLAGS) -o $(NAME) $(INC) $(LIB) $(DEF) $(SRC)

clean:
	@make -C libft/ clean > /dev/null

fclean:
	@make -C libft/ fclean > /dev/null
	@rm -rf $(NAME).dSYM
	@rm -f $(NAME)

re:
	@make fclean
	@make all
