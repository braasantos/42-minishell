NAME = minishell
SRCS = main.c \
parser/split.c \
parser/split_util.c \
parser/parser_util.c \
parser/pad.c \
parser/parser.c \
helpers/bool.c \
helpers/bool_utils.c \
helpers/counters.c \
helpers/helpers.c \
helpers/parser_utils.c \
helpers/parser_utils2.c \
helpers/parser_utils3.c \
helpers/path_helper.c \
helpers/utils.c \
helpers/utils2.c \
helpers/utils3.c \
helpers/quotes.c \
builtins/pwd.c \
builtins/expander_helpers.c \
builtins/expander_helpers2.c \
builtins/expander.c \
builtins/builtins.c \
builtins/cd.c \
builtins/cd_utils.c \
builtins/cd_utils2.c \
builtins/env.c \
builtins/export.c \
builtins/unset.c \
builtins/echo.c \
builtins/echo_utils2.c \
builtins/echo_utils.c \
builtins/export_utils.c \
builtins/export_utils2.c \
error/ft_fprintf.c\
error/error.c \
redirects/redirects.c \
redirects/redirects_utils.c \
redirects/heredoc_utils2.c \
redirects/heredoc_utils.c \
redirects/heredoc.c \
quotes/handle_quotes.c \
quotes/quotes_utils2.c \
quotes/quotes_utils_3.c \
free/free.c \
free/free_utils.c \
execution/exec.c \
pipes/pipes.c \
execution/exec_helper.c \
signals/signals.c \
signals/signals_utils.c \

HEADER = ../inc/minishell.h
LIBFTDIR = includes/LIBFT/libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
COMPILER = $(CC) $(CFLAGS)
RM = rm -f
MINI = -lreadline
SRCS_DIR = srcs/
OBJS_DIR = objs/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
LIBFT = $(LIBFTDIR)

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)  $(LIBFTDIR)
	@echo "Complied chief"
	$(COMPILER) $(OBJS) $(LIBFTDIR) -I includes/LIBFT -o $(NAME) $(MINI)

$(LIBFTDIR):
	$(MAKE) -C includes/LIBFT

%.o: %.c $(HEADER)
	$(COMPILER) -I includes/LIBFT -c $< -o $@

$(OBJS_DIR):
	mkdir -p objs
	mkdir -p objs/builtins/
	mkdir -p objs/error/
	mkdir -p objs/execution/
	mkdir -p objs/free/
	mkdir -p objs/helpers/
	mkdir -p objs/parser/
	mkdir -p objs/pipes/
	mkdir -p objs/quotes/
	mkdir -p objs/redirects/
	mkdir -p objs/signals/

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)
	$(MAKE) -C includes/LIBFT clean
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C includes/LIBFT fclean

re: fclean all

.PHONY: all clean fclean re
