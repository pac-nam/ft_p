##############################################################
######################### BINARIES ###########################
##############################################################

NAME 			= 		libftprintf.a

DEBUG			=		-g3
CFLAGS 			=  		-Wall -Werror -Wextra $(DEBUG)
CC 				= 		gcc $(CFLAGS)
CPPFLAGS		=		-I$(INCLUDES)			\
						-I$(HEADERLIB)			\

##############################################################
########################## COLORS ############################
##############################################################

RED 			= 		\x1b[31m
YELLOW	 		= 		\x1b[33m
GREEN 			= 		\x1b[32m
RESET 			= 		\x1b[0m

##############################################################
#################### SRCS & OBJS FOLDER ######################
##############################################################

SRC_DIR			= 		srcs
OBJ_DIR			= 		objects

##############################################################
########################### LIBFT ############################
############################ LIB #############################
##############################################################

LIBFTDIR		=		libft
LIB				=		libft.a
LIBD      		=		$(LIBFTDIR)/$(LIB)

##############################################################
########################## HEADERS ###########################
##############################################################

INCLUDES 		= 		includes
HEADERLIB   	=   	$(LIBFTDIR)/$(INCLUDES)/
HEADER			=		ft_printf.h internal.h
HEADERS			=		$(addprefix $(INCLUDES)/, $(HEADER))

##############################################################
########################### Padding ##########################
########################## Precision #########################
##############################################################

PAD_PRE_DIR		=		precision_padding

PAD_PRE_SRC		=		ft_putzero.c			\
						ft_get_precision.c		\

PAD_PRE_SRCS	=		$(addprefix $(PAD_PRE_DIR)/, $(PAD_PRE_SRC))

##############################################################
########################### Buffer ###########################
##############################################################

BUFFER_DIR		=		buff

BUFFER_SRC		=		ft_reset_buff.c			\
						ft_put_buffer.c			\
						ft_put_buffer2.c		\
						ft_prefix.c				\
			
BUFFER_SRCS		=		$(addprefix $(BUFFER_DIR)/, $(BUFFER_SRC))

##############################################################
########################### Convert ##########################
##############################################################

CONVERT_DIR		=		convert

CONVERT_SRC		=		ft_convert.c			\
						ft_convert2.c			\
						ft_convert_ptr.c		\
						ft_convert_int.c		\
 						ft_convert_uni.c		\
						ft_convert_uni2.c		\
						ft_convert_unicode.c	\
 						ft_convert_uint.c		\
						ft_convert_unicode2.c 	\

CONVERT_SRCS	=		$(addprefix $(CONVERT_DIR)/, $(CONVERT_SRC))

##############################################################
############################ List ############################
##############################################################

LIST_DIR		=		lst

LIST_SRC		=		ft_init_struct.c		\

LIST_SRCS		=		$(addprefix $(LIST_DIR)/, $(LIST_SRC))

##############################################################
############################ Core ############################
##############################################################

CORE_DIR		=		core

CORE_SRC		=		ft_printf.c				\
						ft_core.c				\
						ft_flags.c				\
						ft_precision.c			\
						ft_modifier.c			\
						ft_types.c				\
						ft_strcatindex.c		\

CORE_SRCS		= 		$(addprefix $(CORE_DIR)/, $(CORE_SRC))

##############################################################
########################### SUBDIR ###########################
##############################################################

OBJS_DIR		=		$(CORE_DIR)				\
						$(LIST_DIR)				\
						$(CONVERT_DIR)			\
						$(BUFFER_DIR)			\
						$(PAD_PRE_DIR)

SRCS			=		$(CORE_SRCS)			\
						$(LIST_SRCS)			\
						$(CONVERT_SRCS)			\
						$(BUFFER_SRCS)			\
						$(PAD_PRE_SRCS)			\


OBJS			=		$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(LIBD) $(OBJ_DIR) $(OBJS)
	@cp $(LIBD) $(NAME)
	@ar rcs $(NAME) $(OBJS)
	@echo "Compiling $(NAME)${RESET} [${GREEN}✔${RESET}]"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@$(CC) -c -o $@ $< $(CPPFLAGS)

$(OBJ_DIR):
	@mkdir -p $(addprefix $@/, $(OBJS_DIR))

$(LIBD):
	@make -C $(LIBFTDIR)/

clean:
	@echo "${RED}Cleaning $(NAME)${RESET} [${GREEN}✔${RESET}]"
	@/bin/rm -rf $(OBJ_DIR);
	@make clean -C $(LIBFTDIR)

fclean: clean
	@echo "${RED}Purge $(NAME)${RESET} [${GREEN}✔${RESET}]"
	@/bin/rm -f $(NAME)
	@make fclean -C $(LIBFTDIR)

re: fclean all


.PHONY: all, clean, fclean, re, $(LIBD)
