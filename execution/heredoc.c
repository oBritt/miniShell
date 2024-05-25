/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:29:04 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/25 13:37:44 by oemelyan         ###   ########.fr       */
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

void read_store_input(t_cmd *command, int nbr) //to fix that if it's only heredoc not to find paths
{
	// printf("read store input\n");
	printf("nbr = %d\n", nbr);

	if (nbr == 1)
		take_n_write(command);
	else if (nbr == 2)
		do_4_two(command, nbr);
	else
	{
		skip_unused_delimiters(command, nbr);
		do_4_two (command, nbr);
	}
}

void set_heredoc(t_cmd *command)
{
	printf("---set heredoc---\n");
	int		nbr;

	nbr = 0;
	while (command->delimiter[nbr])
		nbr++;
	printf("nbr from set heredoc: %d\n", nbr);
	read_store_input(command, nbr);
	//dup2(command->in_fd, 0); //set the input for command
}

void heredoc_check(t_data *data)
{
	printf("---heredoc check---\n");
	int		i;
	int		p;

	i = 0;
	while (i < data->t_cmds[0].amount)
	{
		if (data->t_cmds[i].delimiter && data->t_cmds[i].delimiter[0])
		{
			p = pipe(data->t_cmds[i].heredoc_fd);
			printf("read end fd: %d, write end fd: %d\n", data->t_cmds[i].heredoc_fd[0], data->t_cmds[i].heredoc_fd[1]);
			p_check(p, data);
			set_heredoc(&data->t_cmds[i]);
			//close(data->t_cmds[i].heredoc_fd[0]); //to close after the command execution
			close(data->t_cmds[i].heredoc_fd[1]);
		}
		i++;
	}
}

	//if (data->t_cmds[i].delimiter && data->t_cmds[i].delimiter[0])
	// while (i < data->t_cmds[0].amount)
	// {
	// 	p = pipe(data->t_cmds[i].heredoc_fd);
	// 	printf("read end fd: %d, write end fd: %d\n", data->t_cmds[i].heredoc_fd[0], data->t_cmds[i].heredoc_fd[1]);
	// 	p_check(p, data);
	// 	set_heredoc(&data->t_cmds[i]);
	// 	//close(data->t_cmds[i].heredoc_fd[0]); //to close after the command execution
	// 	close(data->t_cmds[i].heredoc_fd[1]);
	// 	i++;
	// }