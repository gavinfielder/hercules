# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfielder <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/08 11:48:26 by gfielder          #+#    #+#              #
#    Updated: 2019/03/09 16:48:59 by gfielder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ---------------------------------------------------------------------------- #
# Edit this line to specifiy the lab computer the server is running on         #
                                                                               #
SERVER_NAME=e1z2r7p24
                                                                               #
# ---------------------------------------------------------------------------- #
# Use this if you want to change the port                                      #
                                                                               #
SERVER_PORT=24622
                                                                               #
# ---------------------------------------------------------------------------- #

SERVER_IP_1="10.112"
SERVER_IP_2=$(shell echo -n $(SERVER_NAME) | awk -Fr '{print $$2}' | sed "s/p.*$$//g")
SERVER_IP_3=$(shell echo -n $(SERVER_NAME) | awk -Fp '{print $$2}')
SERVER_IP="\"$(SERVER_IP_1).$(SERVER_IP_2).$(SERVER_IP_3)\""

CFLAGS=-D SERVER_IP_ADDRESS=$(SERVER_IP) -D SERVER_PORT=$(SERVER_PORT) -Wall -Wextra -Werror
LIBFTDIR=libft
LIBFTPRINTFDIR=libftprintf
LIB=-L $(LIBFTDIR) -lft -L $(LIBFTPRINTFDIR) -lftprintf
INC=-I $(LIBFTDIR)/includes/ -I inc/ -I $(LIBFTPRINTFDIR)/inc/
LIBFT=$(LIBFTDIR)/libft.a
LIBFTPRINTF=$(LIBFTPRINTFDIR)/libftprintf.a

SERVER_SRC=src/server/main.c src/server/broadcast.c src/server/user.c \
		   src/server/commands.c src/server/help.c src/server/style.c \
		   src/server/daemon.c
CLIENT_SRC=src/client/main.c src/client/listen.c src/client/utils.c

SERVER_ONAME="server"
CLIENT_ONAME="client"

all:
	@echo "Server name is \"$(SERVER_NAME)\". If this is not correct, edit the Makefile and make client or make server."
	@echo "Please specify server or client."
	@echo "usage: \"make server\" or \"make client\""

$(LIBFT):
	@make -C $(LIBFTDIR)

$(LIBFTPRINTF):
	@make -C $(LIBFTPRINTFDIR)

server: $(SERVER_SRC) $(LIBDEPEND)
	@echo "Server name is \"$(SERVER_NAME)\". If this is not correct, edit the Makefile and \`make server\` again."
	@make -C $(LIBFTDIR) > /dev/null
	@make -C $(LIBFTPRINTFDIR) > /dev/null
	@clang $(CFLAGS) $(INC) $(LIB) -o $(SERVER_ONAME) $(SERVER_SRC)
	@echo "DGram Chat Server made. Run with ./$(SERVER_ONAME)"

client: $(CLIENT_SRC) $(LIBDEPEND)
	@echo "Server name is \"$(SERVER_NAME)\". If this is not correct, edit the Makefile and \`make client\` again."
	@make -C $(LIBFTDIR) > /dev/null
	@make -C $(LIBFTPRINTFDIR) > /dev/null
	@clang $(CFLAGS) $(INC) $(LIB) -o $(CLIENT_ONAME) $(CLIENT_SRC)
	@echo "DGram Chat Client made. Run with ./$(CLIENT_ONAME)"

simple_tester: src/simple_tester/main.c
	@echo "Server name is \"$(SERVER_NAME)\". If this is not correct, edit the Makefile and \`make simple_tester\` again."
	@make -C $(LIBFTDIR) > /dev/null
	@make -C $(LIBFTPRINTFDIR) > /dev/null
	@clang $(CFLAGS) $(INC) $(LIB) -o simple_tester src/simple_tester/main.c
	@echo "Simple Tester made. Run with ./simple_tester"

clean:
	@make -C $(LIBFTDIR) clean
	@make -C $(LIBFTPRINTFDIR) clean 

fclean:
	@make -C $(LIBFTDIR) fclean
	@make -C $(LIBFTPRINTFDIR) fclean 
	@rm -rf *.dSYM
	@rm -f $(SERVER_ONAME)
	@rm -f $(CLIENT_ONAME)
	@rm -f simple_tester
	@make clean

re:
	@make fclean
	@make server
	@make client
