/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:19:12 by oemelyan          #+#    #+#             */
/*   Updated: 2024/05/24 17:21:46 by oemelyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../executor.h"

void open_file(t_cmd *command, int i, int redir_number)
{
	printf("--open_file--\n");
    int temp_fd;

	temp_fd = 0;
    temp_fd = open(command->input_redirect[i], O_RDONLY);
    if (temp_fd == -1)
	{
        display_error("minishell: ");
        display_error(strerror(errno));
        display_error("\n");
        exit(EXIT_FAILURE);
    }
    if (i == redir_number - 1 && !command->delimiter[0])
        command->in_fd = temp_fd;
	else
        close(temp_fd);
}

void redir_in_check(t_cmd *command)
{
	printf("--redirect in check ---\n");
	int		i;
	int		redir_number;

	redir_number = 0;
	while(command->input_redirect[redir_number])
		redir_number++;
	i = 0;
	while (i < redir_number)
	{
		if (command->is_ambigious_input[i])
		{
			display_error("minishell: ");
			display_error(strerror(errno));
			display_error("\n");
			exit(EXIT_FAILURE);
		}
		open_file(command, i, redir_number);
		i++;
	}
}

void	open_out_file(t_cmd *command, int i, int redir_number)
{
	printf("--open out file ---\n");
	int		fd;

	fd = 0;
	if (command->is_output_append[i])
		fd = open(command->output_redirect[i], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(command->output_redirect[i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		display_error("minishell: ");
		display_error(strerror(errno));
		display_error("\n");
		exit(EXIT_FAILURE);
	}
	if (i == redir_number - 1)
	{
		command->out_fd = fd;
	}
	return ;
}

void redir_out_check(t_cmd *command)
{
	printf("--redirect out check ---\n");
	int		i;
	int		redir_number;

	redir_number = 0;
	while(command->output_redirect[redir_number])
		redir_number++;
	i = 0;
	while (i < redir_number)
	{
		if (command->is_ambigious_output[i])
		{
			display_error("minishell: ");
			display_error(strerror(errno));
			display_error("\n");
			exit(EXIT_FAILURE);
		}
		open_out_file(command, i, redir_number);
		i++;
	}
}