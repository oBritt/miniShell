/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:03:34 by oemelyan          #+#    #+#             */
/*   Updated: 2024/06/04 15:55:34 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <errno.h>
# include <fcntl.h> //for O_WRONLY O_CREAT O_TRUNC flags
# include "minishell.h"

//execution itself
void		execute_cmd(t_data *data);
void		get_cmd_path(t_data *data, int cmd_index);
void		set_redirections(t_data *data);
void		mult_execute(t_data *data);
void		child(t_data *data, int last_cmd, int i);
void		parent(t_data *data, int last_cmd);
void		p_check(int p, t_data *data);
int			check_if_builtin(char *str);
void		the_only_one_builtin_exe(t_data *data, int i);
void		normal_exe(t_data *data, int last_cmd, int i);
void		last_cmd_check(t_data *data, int last_cmd, int i);
int			execute_builtin(t_data *data, int i, int is_main);
int			if_path_is_still_in_env(t_data *data);

void		execve_check(t_data *data, int last_cmd, int i);
void		first_child_checks(t_data *data, int last_cmd, int i);

//redir in
void		redir_in_check(t_cmd *command);
void		open_file(t_cmd *command, int i, int redir_number, int *fail);
void		redir_out_check(t_cmd *command);

//heredoc
void		heredoc_check(t_data *data);
void		set_heredoc(t_cmd *command, t_data *data);
void		read_store_input(t_cmd *command, int nbr, t_data *data);
void		skip_unused_delimiters(t_cmd *command, int nbr);
void		do_4_two(t_cmd *command, int nbr, t_data *data);
int			reject_check(char *input, t_cmd *command, int nbr);
void		take_n_write(t_cmd *command, t_data *data);
int			input_check(char *str);
void		do_4_helper(t_cmd *command, char *input);

//redir out
void		redir_out_check(t_cmd *command);
void		open_out_file(t_cmd *command, int i, int redir_number, int *fail);

//builtins
int			builtin_cd(t_data *data, char **command, int is_main);
int			pwd(int fd, int is_main);
int			builtin_export(t_data *data, char **command, int fd, int is_main);
int			export_handle(t_data *data, char **command, int is_main);
int			builtin_env(t_data *data, char **command, int fd, int is_main);

//utils
size_t		ft_strlen(const char *str);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t len);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin(char *s1, char *s2);
char		**ft_split1(char const *s, char c);

//errors
void		display_error(char *s);
void		err_127(char *cmd, t_data *data, int nbr);
void		outfile_err(char *s);

#endif