NAME = minishell
SRCS = main.c \
parsing/parsing.c \
pipes/pipes.c \
redirects/redirects.c \
redirects/append_heredoc.c \
signals/signal.c \
signals/signal_handlers.c \
helpers/utils.c \
helpers/utils2.c \
helpers/utils3.c \
helpers/checkers_utils.c \
helpers/utils_commands.c \
helpers/checkers.c \
helpers/parser_helpers.c \
helpers/path_helpers.c \
execution/exec.c \
builtins/builtins.c \
builtins/expander.c \
builtins/expander2.c \
builtins/pwd.c \
builtins/env.c \
builtins/export.c \
builtins/export_utils.c \
builtins/unset.c \
builtins/cd.c \
builtins/cd_util.c \
builtins/echo.c \
builtins/echo_split.c \
builtins/echo_utils.c \
clean_exit/clean_all.c \

HEADER = ../inc/minishell.h
LIBFTDIR = includes/LIBFT/libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
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

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p objs
	mkdir -p objs/builtins/
	mkdir -p objs/clean_exit/
	mkdir -p objs/execution/
	mkdir -p objs/helpers/
	mkdir -p objs/parsing/
	mkdir -p objs/pipes/
	mkdir -p objs/redirects/
	mkdir -p objs/signals/

clean :
	$(RM) $(OBJS)
	$(MAKE) -C includes/LIBFT clean
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C includes/LIBFT fclean

re: fclean all

leak: all
	valgrind --leak-check=full --show-leak-kinds=all \
		--suppressions=readline_leaks ./$(NAME)

.PHONY: all clean fclean re