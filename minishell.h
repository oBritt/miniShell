/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:29:20 by obrittne          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/20 16:17:14 by oemelyan         ###   ########.fr       */
=======
/*   Updated: 2024/05/20 18:49:13 by obrittne         ###   ########.fr       */
>>>>>>> c608c33c9d16a0afe70d65517961d0ed311d6135
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
# include <limits.h>
# include <errno.h>
# include <dirent.h>

typedef struct command
{
	char		**cmd;
	char		*first;
	char		**input_redirect;
	int			*is_ambigious_input;
	char		**output_redirect;
	int			*is_ambigious_output;
	char		**delimiter;
	char		**stored_delimiter;
	char		*cmd_path;
	int			in_fd;
	int			out_fd;
	int			have_to_execute; //for what?
	int			*is_output_append;
	int			amount;
}	t_cmd;

typedef struct s_data
{
	char	*cwd;
	char	**comands;
	char	**env;
	char	**all_env_paths; //I need all paths stored
	char	*home;
	char	**original_env;
	char	**addition_env;
	int		last_exit;
	int		*exit_signal;
	int		origin_stdin; //for execution of several cmds
	int		origin_stdout; //for execution of several cmds
	int		waitpid_status; // same
	int		fd_arr[2]; // for piping
	int		process_id; // for piping
	char	*last_arg;
	char	*cur_last;
	t_cmd	*t_cmds;
	int		should_continue;
	int		exit_printed;
	int		exit;
}	t_data;

typedef struct s_space
{
	char	*str;
	int		pointer1;
	int		pointer2;
	int		one;
	int		two;
	int		action;
	char	*opt1;
	char	*opt2;
	int		last;
}	t_space;

typedef struct s_send
{
	int		inp_out;
	t_cmd	*cmd;
}	t_send;

# define MAX_LLONG "9223372036854775807"
# define MIN_LLONG "9223372036854775808"
# define SHELL_PROMT "minishell > "
# define DELIMITER "<<"
# define INPUT_RED "<"
# define OUTPUT_RED ">"
# define OUTPUT_RED_AP ">>"

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
int			builtin_exit(t_data *data, char **command, int is_main);
long long	ft_atoll(char *str, int *err);
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
int			*full_handle_quotes(t_data *data, char **str);
int			find_first_full_handle(char *str, char app);
int			builtin_echo(t_data *data, char **command, int fd, int is_main);
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
int			check_wild_card(char **str, int *inf);
int			find_nth_app_back_slash(char *str, int number);
int			count_amount_path_back(char *str);
char		**get_folders_in_that_dir(void);
int			len_2d_array(char **array);
int			check_if_same_wild(char *posible, char *wild, int *splitable);
char		get_last_char(char *str);
int			index_equal(char *original, char *find);
int			is_compare_strings_len(char *str1, char *str2, int len);
char		**ft_split(char const *s, char c);
int			freeing_stuff(char **array, int *out);
int			count_app_in2d_array(char **array, char c);
int			*get_array_used_stars(int *information, char **array);
char		**ft_split_wildcard(char *str, int *is_splitable);
int			absolute_handle(t_data *data, char **str);
void		remove_useless_dollar(char *str);
char		**redir(char *str, int **last, char *opt1, char *opt2);
int			get_amount_redirection(char *str, char *opt1, char *opt2);
int			parsing(t_data *data, char *input);
int			get_redir_basic_case(char **output, int *array, char *str, \
t_space *space);
void		set_equal_and_increment(t_space *space, char *str);
int			go_untill_space_end(char **output, t_space *space, char *opt);
int			iterate_and_get_redir(char **commands, t_cmd *cmd);
int			consists_only_of_dollar(char *str);
int			get_len_dollar(char *str);
void		freeing_cmds(t_cmd *cmd);
void		go_untill_quote(t_space *space, char *str);
int			update_delimiter(char **array);
int			parse_addition(t_data *data, char **command, t_cmd *cmd);
int			change_values_command(char **command, t_data *data, t_cmd *cmd);
char		*free_str_return_null(char *str);
int			full_handle_redir(t_data *data, char **str, t_send *send, int i);
char		**get_only_the_same(char **dirs, char *str, int *wild);
int			check_if_have_to_do_smth(int *array);
void		sort_2d_array(char **array);
void		trans(char *wild, int *splitable);
void		detrans(char *wild);
void		detranss(char **s);
int			get_len_dollar(char *str);
int			manage_dollar(t_data *data, char **str);
void		get_rid_of_parantheses(char *str);
int			free_str_return_numb(char *str, int n);
void		remove_first_and_last_one(char *str, char s);
int			fill_array_full_handle(char *str, char **array);
int			check_syntaxes(t_data *data, char *input);
void		output_message_unclosed(char c);
void		output_message_bad_sub(t_space *space, char *input);
void		sort_to_original(char **env, char **original_env);
int			find_by_key(char **env, char *str);
void		sort_to_original(char **env, char **original_env);
int			update_env_value(char ***env, char *str, int ind, int append);
int			get_index_to_insert(char **env, char **original_env, char *str);
char		*itos(long long num);
char		*ft_str_join(char *str1, char *str2);
char		*get_cwd(void);
int			builtin_export(t_data *data, char **command, int fd, int is_main);
char		**join_2d_arrays_same_address(char **arr1, char **arr2);
int			export_handle(t_data *data, char **command, int is_main);
int			check_if_in(char **array, char *str);
int			update_export(t_data *data, char *str);
void		delete_from_addition(t_data *data, char *str);
int			update_export_append(t_data *data, char *str);
int			check_if_valid_export(char *str);
void		error_output_export(char *str);
void		delete_from_array(char **array, int ind);
int			builtin_unset(t_data *data, char **command, int is_main);
#endif