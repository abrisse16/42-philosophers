# COLORS
_GREY		=	$'\033[1;30m
_RED		=	$'\033[1;31m
_GREEN		=	$'\033[1;32m
_YELLOW		=	$'\033[1;33m
_BLUE		=	$'\033[1;34m
_PURPLE		=	$'\033[1;35m
_CYAN		=	$'\033[1;36m
_WHITE		=	$'\033[1;37m
_NO_COLOR	=	$'\033[m

# VARIABLE
NAME	= philo

CC		= gcc

CFLAGS	= -Wall		\
		  -Wextra	\
		  -Werror	\
		  -MMD		\
		  -g
IFLAGS	= -I includes/
LDFLAGS = -pthread

SRCS_PATH	= srcs/
OBJS_PATH	= objs/
DEP_PATH	= deps/

SRCS		= main.c			\
			  parsing.c			\
			  philosophers.c	\
			  activity.c		\
			  monitoring.c		\
			  utils.c			\
			  forks.c			\
			  free.c
OBJS		= $(addprefix $(OBJS_PATH), $(SRCS:.c=.o))
DEP			= $(addprefix $(DEP_PATH), $(SRCS:.c=.d))
vpath %.c $(SRCS_PATH)

# COMPILATION
$(NAME)	: $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)
	@echo "$(_GREEN)[philo: Executable created]$(_NO_COLOR)"

$(OBJS_PATH)%.o : %.c
	@mkdir -p $(OBJS_PATH) $(DEP_PATH)
	@echo "$(_GREY)Compiling : $<$(_NO_COLOR)"
	@$(CC) -o $@ -c $< $(CFLAGS) $(IFLAGS) $(LDFLAGS)
	@mv $(@:.o=.d) $(DEP_PATH)

-include $(DEP)

# RULES
all		: $(NAME)

clean	:
	@rm -rf $(OBJS_PATH)
	@rm -rf $(DEP_PATH)
	@echo "$(_RED)[philo: All objects removed]$(_NO_COLOR)"

fclean	: clean
	@rm -rf $(NAME)
	@echo "$(_RED)[philo: Executable removed]$(_NO_COLOR)"

re		: fclean all

.PHONY	: all clean fclean re
