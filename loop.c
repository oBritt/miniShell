/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obrittne <obrittne@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:25:20 by obrittne          #+#    #+#             */
/*   Updated: 2024/05/20 18:25:52 by obrittne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "executor.h"

int	exit_signal = 0;

static char	*copy(char *str)
{
	char	*output;
	int		i;

	output = malloc(str_len(str) + 3);
	if (!output)
		return (NULL);
	i = 0;
	while (str[i])
	{
		output[i] = str[i];
		i++;
	}
	output[i] = ' ';
	output[i + 1] = ' ';
	output[i + 2] = '\0';
	return (output);
}

void	handle_signals(int status)
{
	char	*str;

	str = copy(rl_line_buffer);
	rl_replace_line(str, 1);
	rl_redisplay();
	write(1, "\n", 1);
	exit_signal = 1;
	//loop forever signal not 0 to do
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
	status--;
}

void	loop(t_data *data)
{
	char	*input;
	int		fd_in;
	int		fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	data->exit_signal = &exit_signal;
	rl_catch_signals = 1;
	if (signal(SIGINT, handle_signals) == SIG_ERR)
	{
		write(2, "Erorr signal issue\n", 19);
		exit(1);
	}
	// for (int i = 0; data->env[i]; i++)
	// 	printf("%s\n", data->env[i]);
	char *asd[5];
	asd[0] = "asd";
	asd[1] = "HOME+=a";
	asd[2] = "asd";
	asd[3] = "d";
	asd[4] = NULL;
	builtin_export(data, asd, 1, 1);
	asd[1] = NULL;
	builtin_export(data, asd, 1, 1);
	while (1)
	{
		input = readline(SHELL_PROMT);
		if (!input)
		{
			write(1, "exit\n", 6);
			break ;
		}
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
		remove_useless_spaces(input);
		remove_useless_dollar(input);
		parsing(data, input);
		t_cmd *cmd = data->t_cmds;
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
				printf("%s    ", cmd[i].delimiter[e]);
			printf("\n");
			printf("\n");
		}
		// write(1, input, str_len(input));
		// write(1, "\n", 1);
		free(input);
		execute_cmd(data);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		free(data->last_arg);
		data->last_arg = data->cur_last;
		data->cur_last = malloc(2);
	}
	clear_history();
}
