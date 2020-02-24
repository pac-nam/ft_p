##############################################################
######################### BINARIES ###########################
##############################################################

CLIENT			= client
SERVER			= server

##############################################################
########################## COLORS ############################
##############################################################

RED 			= 	\x1b[31m
YELLOW	 		= 	\x1b[33m
GREEN 			= 	\x1b[32m
RESET 			= 	\x1b[0m

##############################################################
######################### VARIABLE ###########################
##############################################################

DEBUG			= -g3 #-fsanitize=address
CC				= gcc -Wall -Werror -Wextra $(DEBUG)
TOOLS			= tools

##############################################################
####################### LIBFT & PRINTF #######################
############################ LIB #############################
##############################################################

LIBFTDIR        = libft
PRINTFDIR       = ft_printf
LIB             = libftprintf.a
GLOBDIR       	= glob
LIBGLOB			= libglob.a
OPENSSLDIR		= $(shell brew --prefix)/opt/openssl@1.1/lib

##############################################################
########################## HEADERS ###########################
##############################################################

INCLUDES		= includes

HEADPRINTF      = $(PRINTFDIR)/$(INCLUDES)
HEADERLIB       = $(PRINTFDIR)/$(LIBFTDIR)/$(INCLUDES)
HEADERGLOB      = $(GLOBDIR)/$(INCLUDES)
HEADERSSERVER	= $(INCLUDES)/$(SERVER).h $(INCLUDES)/ft_p.h
HEADERSCLIENT	= $(INCLUDES)/$(CLIENT).h $(INCLUDES)/ft_p.h
HEADERS			= $(INCLUDES)/ft_p.h

##############################################################
######################### LIBRARIES ##########################
##############################################################

LDFLAGS 		= 	-L$(GLOBDIR)	\
					-lglob			\
					-L$(PRINTFDIR)	\
					-lftprintf		\
					-L$(OPENSSLDIR)	\
					-lcrypto

CPPFLAGS		=	-I$(HEADERLIB)	\
					-I$(HEADPRINTF)	\
					-I$(INCLUDES)	\
					-I$(HEADERGLOB) \
					-I$(shell brew --prefix)/Cellar/openssl@1.1/1.1.1d/include

##############################################################
#################### SRCS & OBJS FOLDER ######################
##############################################################

SRCSDIR			= srcs
OBJSDIR			= objects

##############################################################
########################## CLIENT ############################
##############################################################

SRCSDIRCLIENT	= $(SRCSDIR)/$(CLIENT)/
OBJSDIRCLIENT	= $(OBJSDIR)/$(CLIENT)/

SRCCLIENT		=	main.c					\
					prompt.c				\
					read.c					\
					tools.c					\
					users.c					\
					handle_cmd.c			\
					builtin.c				\
					put.c					\
					get.c					\
					cd.c					\
					server_builtin.c		\
					mput.c					\
					mget.c					\

SRCSCLIENT 		= 	$(addprefix $(SRCSDIRCLIENT), $(SRCCLIENT))
OBJCLIENT 		= 	$(SRCCLIENT:%.c=%.o)

OBJSCLIENT 		= 	$(addprefix $(OBJSDIRCLIENT), $(OBJCLIENT))

##############################################################
########################## SERVER ############################
##############################################################

SRCSDIRSERVER 	= $(SRCSDIR)/$(SERVER)/
OBJSDIRSERVER 	= $(OBJSDIR)/$(SERVER)/

SRCSERVER 		=	main.c					\
					init_struct.c			\
					server.c				\
					authentification.c		\
					keep_hand_on_server.c	\
					t_user.c				\
					get_pass_file.c			\
					newdeleteuser.c			\
					showuser.c				\
					client_command.c		\
					put.c					\
					pwd.c					\
					cd.c					\
					get.c					\
					ls.c					\
					mkdir.c					\
					quit.c					\
					verif_access.c			\
					mget.c					\
					connection_accepted.c	\


OBJSERVER 		= 	$(SRCSERVER:%.c=%.o)

SRCSSERVER 		= 	$(addprefix $(SRCSDIRSERVER), $(SRCSERVER))
OBJSSERVER 		= 	$(addprefix $(OBJSDIRSERVER), $(OBJSERVER))

##############################################################
########################### TOOLS ############################
##############################################################

SRCSDIRTOOLS	= $(SRCSDIR)/$(TOOLS)/
OBJSDIRTOOLS	= $(OBJSDIR)/$(TOOLS)/

SRCTOOLS		=	login.c					\
					password.c				\
					env.c					\

OBJTOOLS 		= 	$(SRCTOOLS:%.c=%.o)

SRCSTOOLS 		= 	$(addprefix $(SRCSDIRTOOLS), $(SRCTOOLS))
OBJSTOOLS 		= 	$(addprefix $(OBJSDIRTOOLS), $(OBJTOOLS))


all: $(CLIENT) $(SERVER)

$(OBJSDIR)/$(TOOLS)/%.o: $(SRCSDIR)/$(TOOLS)/%.c $(HEADERS)
	@$(CC) -c -o $@ $< $(CPPFLAGS)

##############################################################
########################## CLIENT ############################
####################### COMPILATION ##########################
##############################################################

$(CLIENT): $(PRINTFDIR)/$(LIB) $(GLOBDIR)/$(LIBGLOB) $(OBJSDIR) $(OBJSTOOLS) $(OBJSCLIENT)
	@echo "Compiling $(CLIENT)${RESET} [${GREEN}✔${RESET}]"
	@$(CC) $(LDFLAGS) $(CPPFLAGS) $(OBJSTOOLS) $(OBJSCLIENT) -o $(CLIENT)

$(OBJSDIR)/$(CLIENT)/%.o: $(SRCSDIR)/$(CLIENT)/%.c $(HEADERSCLIENT)
	@$(CC) -c -o $@ $< $(CPPFLAGS)

##############################################################
########################## SERVER ############################
####################### COMPILATION ##########################
##############################################################

$(SERVER): $(PRINTFDIR)/$(LIB) $(GLOBDIR)/$(LIBGLOB) $(OBJSDIR) $(OBJSTOOLS) $(OBJSSERVER)
	@echo "Compiling $(SERVER)${RESET} [${GREEN}✔${RESET}]"
	@$(CC) $(LDFLAGS) $(CPPFLAGS) $(OBJSTOOLS) $(OBJSSERVER) -o $(SERVER)

$(OBJSDIR)/$(SERVER)/%.o: $(SRCSDIR)/$(SERVER)/%.c $(HEADERSSERVER)
	@$(CC) -c -o $@ $< $(CPPFLAGS)

##############################################################
######################## FT_PRINTF ###########################
####################### COMPILATION ##########################
##############################################################

$(PRINTFDIR)/$(LIB):
	@make -C $(PRINTFDIR)

##############################################################
########################## GLOB ##############################
####################### COMPILATION ##########################
##############################################################

$(GLOBDIR)/$(LIBGLOB):
	@make -C $(GLOBDIR)

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)/{$(CLIENT),$(SERVER),$(TOOLS)}

clean:
	@echo "${RED}Cleaning $(CLIENT)${RESET} [${GREEN}✔${RESET}]"
	@echo "${RED}Cleaning $(SERVER)${RESET} [${GREEN}✔${RESET}]"
	@/bin/rm -rf $(OBJSDIR)
	@make clean -C $(PRINTFDIR)
	@make clean -C $(GLOBDIR)

fclean: clean
	@echo "${RED}Purge $(CLIENT) / $(SERVER)${RESET} [${GREEN}✔${RESET}]"
	@/bin/rm -f $(CLIENT) $(SERVER)
	@make fclean -C $(PRINTFDIR)
	@make fclean -C $(GLOBDIR)

re: fclean all

.PHONY:

.SUFFIXES: .c .o
