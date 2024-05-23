/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:03:34 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/23 20:56:31 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include <errno.h>
# include <fcntl.h> //for O_WRONLY O_CREAT O_TRUNC flags
#include "minishell.h"

//execution itself
void		execute_cmd(t_data *data);
void		get_paths(t_data *data);
void 		mult_execute(t_data *data);
void		child(t_data *data, int last_cmd, int i);
void		parent(t_data *data, int last_cmd);
void		p_check(int p, t_data *data);
int			check_if_builtin(char *str);

//redir in
void		redir_in_check(t_cmd *command);
void		open_file(t_cmd *command, int i, int redir_number);

//heredoc
void		set_heredoc(t_cmd *command);
void		read_store_input(t_cmd *command, int nbr);
void		skip_unused_delimiters(t_cmd *command, int nbr);
void		do_4_two(t_cmd *command, int nbr);
int			reject_check(char *input, t_cmd *command, int nbr);
void		take_n_write(t_cmd *command);

//redir out
void		redir_out_check(t_cmd *command);
void		open_out_file(t_cmd *command, int i, int redir_number);

//builtins
int			builtin_cd(t_data *data, char **command, int is_main);

//utils
size_t		ft_strlen(const char *str);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t len);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char *s1, char *s2);
char		**ft_split1(char const *s, char c);

//errors
void		display_error(char *s);

#endif