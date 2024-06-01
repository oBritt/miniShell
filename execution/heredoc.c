/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:29:04 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/31 18:03:32 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"
#include "../minishell.h"

void	skip_unused_delimiters(t_cmd *command, int nbr)
{
	int		count;
	char	*input;

	count = 0;
	while (get_signal()->should_stop == 0 && count != nbr - 2)
	{
		input = readline("> ");
		if (!input_check(input))
			break ;
		if (!ft_strcmp(input, command->delimiter[count]))
			count++;
		free(input);
	}
}

void	read_store_input(t_cmd *command, int nbr, t_data *data)
{
	if (nbr == 1)
		take_n_write(command, data);
	else if (nbr == 2)
		do_4_two(command, nbr, data);
	else
	{
		skip_unused_delimiters(command, nbr);
		do_4_two (command, nbr, data);
	}
}

void	set_heredoc(t_cmd *command, t_data *data)
{
	int		nbr;

	nbr = 0;
	while (command->delimiter[nbr])
		nbr++;
	printf("nbr from set heredoc: %d\n", nbr);
	read_store_input(command, nbr, data);
	get_signal()->hereidoc = 0;
	get_signal()->should_stop = 0;
}

void	heredoc_check(t_data *data)
{
	int		i;
	int		p;

	i = 0;
	get_signal()->hereidoc = 1;
	while (i < data->t_cmds[0].amount)
	{
		if (data->t_cmds[i].delimiter && data->t_cmds[i].delimiter[0])
		{
			data->t_cmds[i].redir_failed = 0;
			p = pipe(data->t_cmds[i].heredoc_fd);
			p_check(p, data);
			set_heredoc(&data->t_cmds[i], data);
			close(data->t_cmds[i].heredoc_fd[1]);
		}
		i++;
	}
}
