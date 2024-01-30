#---------------VARIAVEIS-----------#
NAME = libft.a

SRCS = ft_isdigit.c \
	ft_strlen.c \
	ft_isalpha.c \
	ft_isascii.c \
 	ft_isprint.c \
 	ft_isalnum.c \
 	ft_toupper.c \
 	ft_tolower.c \
 	ft_atoi.c \
 	ft_strncmp.c \
 	ft_strlcat.c\
	ft_memset.c \
	ft_memmove.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memchr.c \
	ft_strlcpy.c \
	ft_bzero.c \
	ft_strrchr.c \
	ft_strchr.c \
	ft_strnstr.c \
	ft_strdup.c \
	ft_strmapi.c \
	ft_calloc.c \
	ft_itoa.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strtrim.c \
	ft_split.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_printf.c \
	ft_putadress.c \
	ft_put_char.c \
	ft_puthexa.c \
	ft_put_nbr.c \
	ft_put_str.c \
	ft_putunsig.c 

BONUS = ft_lstnew.c \
	ft_lstadd_front.c \
	ft_lstsize.c \
	ft_lstlast.c \
	ft_lstadd_back.c\
	ft_lstdelone.c \
	ft_lstclear.c \
	ft_lstiter.c \
	ft_lstmap.c 

HEADER = libft.h

OBJS = $(SRCS:.c=.o)
OBJSB = $(BONUS:.c=.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra 
COMPLIER = $(CC) $(CFLAGS)
RM = rm -f
#------------REGRAS--------------#
#compila o projeto
all: $(NAME)

%.o : %.c 
	$(COMPLIER) -c $< -o $@

$(NAME): $(OBJS) $(HEADER)
	ar rcs $(NAME) $(OBJS)

#limpa os arquivos criados na compilacao
clean:
	$(RM) $(OBJS) $(OBJSB)

#limpa os arquivos criados e mas tambem a biblioteca estatica
fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus: $(OBJS) $(OBJSB)
	ar rcs $(NAME) $(OBJSB) $(OBJS)

.PHONY: all clean fclean re
# .SILENT:
