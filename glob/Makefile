##############################################################
######################### BINARIES ###########################
##############################################################

NAME			=		libglob.a

SRCSDIR			=		srcs
OBJSDIR			=		objects
FT_PRINTFDIR	=		../ft_printf

##############################################################
######################### VARIABLE ###########################
##############################################################

DEBUG			=	 -g3 #-fsanitize=address
CC				= 	gcc -Wall -Werror -Wextra $(DEBUG)
CPPFLAGS		= 	-Iincludes/							\
					-I$(FT_PRINTFDIR)/includes/			\
					-I$(FT_PRINTFDIR)/libft/includes/	\

##############################################################
########################## COLORS ############################
##############################################################

RED 			= 	\x1b[31m
YELLOW	 		= 	\x1b[33m
GREEN 			= 	\x1b[32m
RESET 			= 	\x1b[0m

##############################################################
########################## FT_GLOB ###########################
##############################################################

SRCGLOB			=	globbing.c				\
					list_glob.c				\
					parse_glob.c			\
					split_pattern_star.c	\
					free_glob.c				\


SRCSGLOB 		= 	$(addprefix $(SRCSDIR)/, $(SRCGLOB))
OBJGLOB 		= 	$(SRCGLOB:%.c=%.o)

OBJSGLOB 		= 	$(addprefix $(OBJSDIR)/, $(OBJGLOB))

##############################################################
########################### GLOB #############################
####################### COMPILATION ##########################
##############################################################

all: $(NAME)

$(NAME): $(OBJSDIR) $(OBJSGLOB)
	@echo "Compiling $(NAME)${RESET} [${GREEN}✔${RESET}]"
	@ar rcs $(NAME) $(OBJSGLOB)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@$(CC) -c -o $@ $< $(CPPFLAGS) $(LDFLAGS)

$(OBJSDIR):
	@mkdir -p $(OBJSDIR)

clean:
	@echo "$(RED)Cleaning objects$(RESET)"
	@rm -rf $(OBJSDIR)

fclean: clean
	@echo "${RED}Purge $(NAME)${RESET} [${GREEN}✔${RESET}]"
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, $(NAME), $(OBJSDIR), clean, fclean, re, $(FT_PRINTFDIR)/$(LIB)