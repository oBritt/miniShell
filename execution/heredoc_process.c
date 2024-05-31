/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_process.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:31:42 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/31 14:30:19 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"
#include "../minishell.h"

int input_check (char *str)
{
	if (!str)
	{
		free (str);
		return (0);
	}
	else
		return (1);
}

void take_n_write(t_cmd *command, t_data *data)
{
	printf("--take n write--\n");
	char	*input;

	input = readline("> ");
	while (get_signal()->should_stop == 0 && ft_strcmp(input, command->delimiter[0]))
	{
		if(!input)
			break ;
		//printf("--len of input: %zu, len of delim: %zu--\n", ft_strlen(input), ft_strlen(command->delimiter[0]));
		if (!manage_dollar(data, &input, 1))
			exit(1);
		//ft_decrypt(input);
		write(command->heredoc_fd[1], input, ft_strlen(input));
		write(command->heredoc_fd[1], "\n", 1);
		free(input);
		input = readline("> ");
		if(!input_check(input))
			break ;
	}
	if (get_signal()->should_stop == 1)
		get_signal()->should_stop = 0;
	if (input)
		free(input);
}


int reject_check(char *input, t_cmd *command, int nbr)
{
	int		i;

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

void do_4_two(t_cmd *command, int nbr, t_data *data)
{
	char		*input;

	input = readline("> ");
	while (ft_strcmp(input, command->delimiter[nbr - 2])) //not a delim
	{
		free(input);
		input = readline("> ");
		if (!input_check(input))
			break ;
	}
	free(input);
	input = readline("> ");
	if (!input_check(input))
		return ;
	while(ft_strcmp(input, command->delimiter[nbr - 1]))
	{
		if (!reject_check(input, command, nbr))
		{
			if (!manage_dollar(data, &input))
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
	close(command->heredoc_fd[1]);//added ch
	if (input)
		free(input);
}

void skip_unused_delimiters(t_cmd *command, int nbr)
{
	int		count;
	char	*input;

	count = 0;
	while (count != nbr - 2)
	{
		input = readline("> ");
		if (!input_check(input))
			break ;
		if (!ft_strcmp(input, command->delimiter[count]))
			count++;
		free(input);
	}
}
