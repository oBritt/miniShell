/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:29:20 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/10 21:39:19 by obrittne         ###   ########.fr       */
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
# include <dirent.h>

typedef struct command
{
	char		**cmd;
	char		*cmd_path;
	int			in_fd;
	int			out_fd;
	int			redir_type; // 0 - infile; 1 - outfile; 2 - append; I actually don't need it if I get from parsing ready fd
	char		*delimiter;
}	t_cmd;

typedef struct s_data
{
	int		redirect_input;
	char	*redirect_input_to;
	int		redirect_output;
	char	*redirect_output_to;
	int		redirect_output_append;
	char	*cwd;
	char	**comands;
	char	**env;
	char	*home;
	char	**original_env;
	char	*last;
	int		*exit_signal;
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
int			count_words_split(char *s, char c);
int			count_len_quotes(char *str);
int			full_handle_quotes(t_data *data, char **str);
int			find_first_full_handle(char *str, char app);
int			builtin_echo(t_data *data, char *str);
char		*transform_to_1d_space(char **array);
int			trans_dol(t_data *data, char **array, int *i, char *str);
int			transform_path_variable(t_data *data, char **str);
int			is_alpha(char c);
int			is_number(char c);
int			evaluate_dollar(char **array, char *str, int *i, int *ptr);
int			is_number_or_question(char c);
void		special_freeing(char **array, int ind);
int			fill_2d_array(char **array, char *str, int i);
int			update_all_dollars(t_data *data, char **array);
int			final_transformation(char **array, char **str);
int			no_quotes(t_data *data, char **str);
int			get_untill_dollar(char **array, char *str, int *i, int *ptr);
int			is_white_space(char c);
int			check_wild_card(char **str);
int			find_nth_app_back_slash(char *str, int number);
int			count_amount_path_back(char *str);
char		**get_folders_in_that_dir(void);
int			len_2d_array(char **array);
int			check_if_same_wild(char *posible, char *wild);
char		get_last_char(char *str);
int			index_equal(char *original, char *find);
int			is_compare_strings_len(char *str1, char *str2, int len);
char		**ft_split(char const *s, char c);
#endif