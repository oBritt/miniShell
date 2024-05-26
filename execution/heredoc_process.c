/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:31:42 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/26 14:32:00 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"
#include "../minishell.h"

void take_n_write(t_cmd *command)
{
	char	*input;

	input = readline("> ");
	while (strncmp(input, command->delimiter[0], ft_strlen(input)))
	{
		write(command->heredoc_fd[1], input, ft_strlen(input));
		write(command->heredoc_fd[1], "\n", 1);
		free(input);
		input = readline("> ");
	}
}

int reject_check(char *input, t_cmd *command, int nbr)
{
	int		i;

	i = 0;
	while (i < nbr - 2)
	{
		if (strncmp(input, command->delimiter[i], ft_strlen(input)))
			i++;
		else
			return (1);
	}
	return (0);
}

void do_4_two(t_cmd *command, int nbr)
{
	char		*input;

	input = readline("> ");
	while (strncmp(input, command->delimiter[nbr - 2], ft_strlen(input)))
	{
		free(input);
		input = readline("> ");
	}
	free(input);
	input = readline("> ");
	while(strncmp(input, command->delimiter[nbr - 1], ft_strlen(input)))
	{
		if (!reject_check(input, command, nbr))
		{
			write(command->heredoc_fd[1], input, ft_strlen(input));
			write(command->heredoc_fd[1], "\n", 1);
		}
		free(input);
		input = readline("> ");
	}
	close(command->heredoc_fd[1]);//added ch
}

void skip_unused_delimiters(t_cmd *command, int nbr)
{
	int		count;
	char	*input;

	count = 0;
	while (count != nbr - 2)
	{
		input = readline("> ");
		if (!strncmp(input, command->delimiter[count], ft_strlen(input)))
			count++;
		free(input);
	}
}