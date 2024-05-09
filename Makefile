CFLAGS = -Wall -Wextra -Werror

SRCS = main.c loop.c parser.c init_data.c \
strings/strings_utils.c strings/put_nbr_fd.c strings/atoll.c strings/find_value.c strings/quotes.c  strings/transform2dto1d.c  strings/ft_split_respect_quotes_help.c \
strings/utils_string_alocation_env.c strings/remove_spaces.c strings/strings_utils2.c strings/single_quotes.c strings/ft_split_respect_quotes.c \
builtins/builtins.c builtins/exit.c

OBJS = $(SRCS:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) -o $(NAME) -lreadline

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re