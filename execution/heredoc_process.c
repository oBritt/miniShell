/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:31:42 by oemelyan          #+#    #+#             */
/*   Updated: 2024/06/04 15:55:40 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"
#include "../minishell.h"

int	input_check(char *str)
{
	if (!str)
	{
		free(str);
		return (0);
	}
	else
		return (1);
}

void	take_n_write(t_cmd *command, t_data *data)
{
	char	*input;

	if (get_signal()->should_stop)
		return ;
	input = readline("> ");
	if (!input_check(input))
		return ;
	while (get_signal()->should_stop == 0 && ft_strcmp(input,
			command->delimiter[0]))
	{
		if (!input_check(input))
			break ;
		if (!manage_dollar(data, &input, 1))
			exit(1);
		write(command->heredoc_fd[1], input, ft_strlen(input));
		write(command->heredoc_fd[1], "\n", 1);
		free(input);
		input = readline("> ");
		if (!input_check(input))
			break ;
	}
	if (input)
		free(input);
}

int	reject_check(char *input, t_cmd *command, int nbr)
{
	int	i;

	i = 0;
	while (i < nbr - 2)
	{
		if (ft_strcmp(input, command->delimiter[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

void	skip_second_last(t_cmd *command, int nbr)
{
	char	*input;

	if (get_signal()->should_stop)
		return ;
	input = readline("> ");
	if (!input_check(input))
		return ;
	while (get_signal()->should_stop == 0 && ft_strcmp(input,
			command->delimiter[nbr - 2]))
	{
		free(input);
		input = readline("> ");
		if (!input_check(input))
			break ;
	}
	if (input)
		free(input);
}

void	do_4_two(t_cmd *command, int nbr, t_data *data)
{
	char	*input;

	skip_second_last(command, nbr);
	if (get_signal()->should_stop)
		return ;
	input = readline("> ");
	if (!input_check(input))
		return ;
	while (get_signal()->should_stop == 0 && ft_strcmp(input,
			command->delimiter[nbr - 1]))
	{
		if (!reject_check(input, command, nbr))
		{
			if (!manage_dollar(data, &input, 1))
				exit(1);
			ft_decrypt(input);
			write(command->heredoc_fd[1], input, ft_strlen(input));
			write(command->heredoc_fd[1], "\n", 1);
		}
		free(input);
		input = readline("> ");
		if (!input_check(input))
			break ;
	}
	do_4_helper(command, input);
}
