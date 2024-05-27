/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oemelyan <oemelyan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:25:20 by obrittne          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/05/27 20:57:28 by oemelyan         ###   ########.fr       */
=======
/*   Updated: 2024/05/27 20:51:34 by obrittne         ###   ########.fr       */
>>>>>>> 18a04f03b718844bf28b8fcd82a33d228635898a
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

void	loop(t_data *data)
{
	char	*input;
	int		fd_in;
	int		fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	rl_catch_signals = 1;

	// for (int i = 0; data->env[i]; i++)
	// 	printf("%s\n", data->env[i]);
	init_signals(data);
	while (data->should_continue && !data->signal->error)
	{
		input = readline(SHELL_PROMT);
		if (!input)
			break ;
		if (!compare_strings("", input))
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (!check_syntaxes(data, input))
		{
			free(input);
			continue ;
		}
		remove_useless_dollar(input);
		parsing(data, input);
<<<<<<< HEAD
		t_cmd *cmd = data->t_cmds;
=======
		 t_cmd *cmd = data->t_cmds;
>>>>>>> 18a04f03b718844bf28b8fcd82a33d228635898a
		for (int i = 0; cmd->amount > i; i++)
		{
			printf("command: ");
			for (int e = 0; cmd[i].cmd[e]; e++)
				printf(" -->%s<--", cmd[i].cmd[e]);
			printf("\ninput  :");
			for (int e = 0; cmd[i].input_redirect[e]; e++)
				printf("%s %i    ", cmd[i].input_redirect[e], cmd[i].is_ambigious_input[e]);
			printf("\noutput  :");
			for (int e = 0; cmd[i].output_redirect[e]; e++)
				printf("%s %i  %i    ", cmd[i].output_redirect[e], cmd[i].is_ambigious_output[e], cmd[i].is_output_append[e]);
			printf("\ndelimiter   :" );
			for (int e = 0; cmd[i].delimiter[e]; e++)
				printf("-->%s<--    ", cmd[i].delimiter[e]);
			printf("\n");
			printf("\n");
		}
<<<<<<< HEAD
		write(1, input, str_len(input));
		write(1, "\n", 1);
=======
		// write(1, input, str_len(input));
		// write(1, "\n", 1);
>>>>>>> 18a04f03b718844bf28b8fcd82a33d228635898a
		free(input);
		get_signal()->is_execution = 1;
		data->last_exit = 0;
		execute_cmd(data);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		free(data->last_arg);
		data->last_arg = data->cur_last;
		data->cur_last = malloc(2);
		freeing_cmds(data->t_cmds);

		get_signal()->is_execution = 0;
		data->last_exit = data->waitpid_status;
	}
	if (!data->exit_printed)
		write(1, "exit\n", 5);
	clear_history();
}
