NAME = minishell
SRCS = main.c \
parsing/parsing.c \
parsing/parsing2.c \
error/ft_fprintf.c \
pipes/pipes.c \
redirects/redirects.c \
redirects/redirects_utils.c \
redirects/append_heredoc.c \
signals/signal_handlers.c \
signals/signal_utils.c \
helpers/utils.c \
helpers/bool_utils.c \
helpers/bool.c \
helpers/utils2.c \
helpers/utils3.c \
helpers/utils4.c \
helpers/utils5.c \
helpers/utils6.c \
helpers/utils7.c \
helpers/checkers_utils.c \
helpers/utils_commands.c \
helpers/checkers.c \
helpers/checkers2.c \
helpers/parser_helpers.c \
helpers/path_helpers.c \
execution/exec.c \
execution/exec_utils.c \
builtins/builtins.c \
builtins/builtins_utils.c \
builtins/expander.c \
builtins/expander2.c \
builtins/expander3.c \
builtins/export_util.c \
builtins/pwd.c \
builtins/env.c \
builtins/export.c \
builtins/export2.c \
builtins/export3.c \
builtins/export_utils.c \
builtins/unset.c \
builtins/cd.c \
builtins/cd2.c \
builtins/cd_util.c \
builtins/echo.c \
builtins/new_split.c \
builtins/echo_utils.c \
builtins/echo_utils2.c \
builtins/echo_utils3.c \
clean_exit/clean_all.c \
clean_exit/clean_all2.c \

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

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p objs
	mkdir -p objs/builtins/
	mkdir -p objs/error/
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
