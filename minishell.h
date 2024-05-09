/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:29:20 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/09 10:37:50 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <string.h>

typedef struct s_data
{
	int		redirect_input;
	char	*redirect_input_to;
	int		redirect_output;
	char	*redirect_output_to;
	int		redirect_output_append;
	char	**comands;
	char	**env;
	char	*home;
	char	**original_env;
	char	*last;
}	t_data;

typedef struct s_space
{
	char	*str;
	int		pointer1;
	int		pointer2;
	int		one;
	int		two;
	int		action;
}	t_space;

# define MAX_LLONG "9223372036854775807"
# define MIN_LLONG "9223372036854775808"
# define SHELL_PROMT "minishell > "

char		**allocate(char **env);
char		**freeing(char **output);
char		*find_string(char *str, char *to_find);
void		loop(t_data *data);
int			init_signals(void);
int			str_len(char *str);
char		*get_first_word(char *str);
int			compare_strings(char *str1, char *str2);
void		remove_useless_spaces(char *str);
void		init_space(t_space *space, char *str);
void		put_nbr_fd(long long num, int fd);
int			is_numeric(char *str);
int			ft_exit(char *str);
long long	ft_atoll(char *str);
int			get_exit_code(char *str);
int			init_data(t_data *data, char **env);
char		*ft_str_dup(char *str);
char		*find_by_value(t_data *data, char *str);
int			single_quotes(char **str);
char		*ft_str_dup_len(char *str, int len);
int			find_first_app(char *str, char app, char stop, char add);
char		*transform_to_1d(char **array);
int			double_quotes(t_data *data, char **str);
char		**ft_split_respect_quotes(char const *s, char c);
int			count_words_split(char *s, char c);
void		validate_quotes_split(t_space *space, char *s);
#endif