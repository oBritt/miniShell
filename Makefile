CFLAGS = -Wall -Wextra -Werror

SRCS = main.c loop.c  init_data.c init_env_standart.c freeing.c init_data_h.c \
strings/strings_utils.c strings/put_nbr_fd.c strings/atoll.c strings/find_value.c strings/quotes.c  strings/transform2dto1d.c  strings/ft_split_respect_quotes_help.c \
strings/utils_string_alocation_env.c strings/remove_spaces.c strings/strings_utils2.c strings/single_quotes.c strings/ft_split_respect_quotes.c \
strings/full_handle_quotes.c strings/full_handle_quotes_h.c strings/transform_path_variable.c  strings/quotes_dollar.c strings/quotes_no.c \
strings/strings_utils3.c strings/slashes_path.c strings/ft_split.c strings/absolute_full_handle.c strings/strings_utils4.c strings/remove_dollar.c \
strings/consists_only_of_dollar.c strings/sort_2d_array.c strings/manage_dollar.c strings/itos.c strings/ft_join.c strings/manage_dollar_h.c \
strings/transform2dto1dv2.c \
syntax/check_syntaxes.c syntax/error_messages.c syntax/check_redirect.c syntax/helper_redir.c \
parsing/parsing.c parsing/get_redir.c parsing/get_redirection_len.c parsing/get_redir_h.c parsing/get_all_redir.c parsing/update_delimiter.c \
parsing/parsing_fill_redirect.c parsing/parsing_change_values_command.c parsing/full_handle_redirection.c parsing/split_wildcard.c \
wildcard/handle_wild_card.c wildcard/get_folders.c wildcard/check_if_same_wild.c wildcard/get_array_used_wild.c wildcard/ft_split_wildcard.c wildcard/transit.c \
builtins/builtins.c builtins/exit.c builtins/echo.c builtins/cd.c builtins/export.c builtins/env.c builtins/unset.c builtins/pwd.c builtins/export_h.c builtins/cd_h.c \
env/check_if_in.c env/sort_env.c env/update_env.c env/handle_update.c \
execution/exe_start.c execution/cmd_paths.c execution/pipe_n_execute.c execution/execution.c execution/heredoc_process.c \
execution/exe_utils/error_msg.c execution/exe_utils/ft_split.c execution/exe_utils/ft_strjoin.c execution/exe_utils/ft_strnstr.c \
execution/exe_utils/libft.c execution/heredoc.c execution/redirections.c execution/pipe_n_execute2.c\
signals/init_signals.c signals/init_signals_h.c

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