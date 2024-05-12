CFLAGS = -Wall -Wextra -Werror

SRCS = main.c loop.c parser.c init_data.c \
strings/strings_utils.c strings/put_nbr_fd.c strings/atoll.c strings/find_value.c strings/quotes.c  strings/transform2dto1d.c  strings/ft_split_respect_quotes_help.c \
strings/utils_string_alocation_env.c strings/remove_spaces.c strings/strings_utils2.c strings/single_quotes.c strings/ft_split_respect_quotes.c \
strings/full_handle_quotes.c strings/full_handle_quotes_h.c strings/transform_path_variable.c  strings/quotes_dollar.c strings/quotes_no.c \
strings/strings_utils3.c strings/slashes_path.c strings/ft_split.c strings/absolute_full_handle.c strings/strings_utils4.c strings/remove_dollar.c \
syntax/check_syntaxes.c \
parsing
wildcard/handle_wild_card.c wildcard/get_folders.c wildcard/check_if_same_wild.c wildcard/get_array_used_wild.c wildcard/ft_split_wildcard.c\
builtins/builtins.c builtins/exit.c builtins/echo.c \

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