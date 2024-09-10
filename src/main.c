/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gandre-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:32:36 by gandre-d          #+#    #+#             */
/*   Updated: 2024/03/12 18:32:37 by gandre-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

t_data	*data(void)
{
	static t_data data;

	return (&data);
}

void	get_path(char **envp)
{
	int		i;

	i = -1;
	while(envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 4))
			break;
	}
	data()->path = envp[i] + 5;
}

t_process *get_commands(int argc, char **argv)
{
	int		i;
	t_process *head;
	t_process *temp;

	i = 0;
	head = NULL;
	while(++i <= argc - 2)
	{
		temp = new_node(argv[i]);
		if (i == 1)
			temp->fd[0] = data()->fd_in;
		else if (i == argc - 2)
			temp->fd[1] = data()->fd_out;
		list_add(&head, temp);
	}
	if (head)
		head->fd_in = data()->fd_in;
	if (temp)
		temp->fd_out = data()->fd_out;
	return head;
}

void ft_close(int *fd)
{
	if (*fd > 1)
		close(*fd);
	*fd = -1;
}


void	exec(t_process *cmds, int in, int out, char **envp)
{
	char	*path;

	path = check_command(data()->path, cmds->coms_array[0]);
	if (fork() == 0)
	{
		dup2(in, STDIN_FILENO);
		ft_close(&in);
		dup2(out, STDOUT_FILENO);
		ft_close(&out);
		if (execve(path, cmds->coms_array, envp) == -1)
		{
			free(path);
			free_nodes();
			write(2, "Command not found\n", 18);
			exit(127);
		}
	}
	ft_close(&in);
	ft_close(&out);
	free(path);
}

int main(int argc, char **argv, char **envp)
{
	int		i;
	int		help;
	t_process *cmd;
	int in = 0;
	int out = 1;

	i = 1;
	help = 0;
	// if (!ft_strncmp(argv[1], "here_doc", 8))
	// {
	// 	argv = here_doc(&argc, argv);
	// 	help = 1;
	// }
	check_args(argc, argv, envp, help);
	get_path(envp);
	data()->cmds = get_commands(argc, argv);
	cmd = data()->cmds;
	while (cmd)
	{
		if (cmd->next)
		{	
			pipe(cmd->fd);
			out = cmd->fd[1];
		}
		if (cmd->fd_in != -1)
		{
			ft_close(&in);
			in = cmd->fd_in;
		}
		if (cmd->fd_out != -1)
		{
			ft_close(&out);
			out = cmd->fd_out;
		}
		exec(cmd, in, out, envp);
		in = cmd->fd[0];
		cmd = cmd ->next;
	}
	cmd = data()->cmds;
	while (cmd)
	{
		wait(NULL);
		cmd = cmd ->next;
	}
	free_nodes();
	if (help)
		free_matrix(argv);
}
