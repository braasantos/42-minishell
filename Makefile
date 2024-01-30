NAME = minishell
SRCS = srcs/1-main.c 
HEADER = ../inc/minishell.h
LIBFTDIR = includes/LIBFT/libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
COMPILER = $(CC) $(CFLAGS)
RM = rm -f
OBJS = $(SRCS:.c=.o)
MINI = -lreadline
all: $(NAME)

$(NAME): $(OBJS) $(LIBFTDIR)
	@echo "Complied chief"
	$(COMPILER) $(OBJS) $(LIBFTDIR) -I includes/LIBFT -o $(NAME) $(MINI)

$(LIBFTDIR):
	$(MAKE) -C includes/LIBFT

%.o: %.c $(HEADER)
	$(COMPILER) -I includes/LIBFT -c $< -o $@

clean:
	@echo "Deleted chief"
	$(RM) $(OBJS)
	$(MAKE) -C includes/LIBFT clean

fclean: clean
	@echo "Deleted Everything chief"
	$(RM) $(NAME)
	$(MAKE) -C includes/LIBFT fclean

re: fclean all
.PHONY: all clean fclean re