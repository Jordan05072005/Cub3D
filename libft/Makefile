SRCS= ft_isalnum.c ft_isprint.c ft_isdigit.c  ft_putchar_fd.c ft_split.c \
	ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c ft_memset.c\
	ft_itoa.c   ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c ft_memcmp.c ft_memcpy.c\
	ft_strnstr.c ft_tolower.c ft_memmove.c ft_isascii.c ft_memchr.c ft_bzero.c\
	ft_toupper.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c ft_calloc.c\
	ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c \
	get_next_line.c get_next_line_utils.c ft_strslen.c
OBJS = $(SRCS:.c=.o)

BONUS= ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
					ft_lstmap.c ft_lstnew.c ft_lstsize.c

OBJS_BONUS = $(BONUS:.c=.o)

CC= clang
RM= rm -f
CFLAGS= -Wall -Wextra -Werror -fPIC -I.

NAME= libft.a

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
		@ar rcs $(NAME) $(OBJS)

clean : 
		@$(RM) $(OBJS) $(OBJS_BONUS)

fclean : clean
		@$(RM) $(NAME)

re :fclean $(NAME)

bonus : $(OBJS) $(OBJS_BONUS)
		@ar rcs $(NAME) $(OBJS) $(OBJS_BONUS)

.PHONY:	all clean fclean re bonus
