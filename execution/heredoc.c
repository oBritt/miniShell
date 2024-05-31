/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:29:04 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/30 22:03:38 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../executor.h"
#include "../minishell.h"

void read_store_input(t_cmd *command, int nbr, t_data *data) //to fix that if it's only heredoc not to find paths
{
	printf("nbr = %d\n", nbr);

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

void set_heredoc(t_cmd *command, t_data *data)
{
	//printf("---set heredoc---\n");
	int		nbr;

	nbr = 0;
	while (command->delimiter[nbr])
		nbr++;
	printf("nbr from set heredoc: %d\n", nbr);
	read_store_input(command, nbr, data);
}

void heredoc_check(t_data *data)
{
	//printf("---heredoc check---\n");
	int		i;
	int		p;

	i = 0;
	while (i < data->t_cmds[0].amount)
	{
		if (data->t_cmds[i].delimiter && data->t_cmds[i].delimiter[0])
		{
			data->t_cmds[i].redir_failed = 0;
			p = pipe(data->t_cmds[i].heredoc_fd);
			//printf("read end fd: %d, write end fd: %d\n", data->t_cmds[i].heredoc_fd[0], data->t_cmds[i].heredoc_fd[1]);
			p_check(p, data);
			set_heredoc(&data->t_cmds[i], data);
			close(data->t_cmds[i].heredoc_fd[1]);
		}
		i++;
	}
}
