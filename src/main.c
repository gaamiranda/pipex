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
		else
		{
			if (pipe(temp->fd) == -1)
			{
				write(1, "Error creating pipe\n", 20);
				exit(1);
			}
		}
		list_add(&head, temp);
	}
	return head;
}

void	exec(t_process *cmds, int in, int out, char **envp)
{
	char	*path;

	path = check_command(data()->path, cmds->coms_array[0]);
	if (fork() == 0)
	{
		dup2(in, STDIN_FILENO);
		dup2(out, STDOUT_FILENO);
		close(in);
		close(out);
		if (execve(path, cmds->coms_array, envp) == -1)
		{
			free(path);
			free_nodes();
			close(data()->fd_out);
			//close(cmds->fd[0]);
			write(2, "Command not found\n", 18);
			exit(1);
		}
	}
	close(in);
	close(out);
	free(path);
	if (cmds->next)
		exec(cmds->next, cmds->fd[0], cmds->next->fd[1], envp);
}

int main(int argc, char **argv, char **envp)
{
	int		i;
	int		help;
	
	i = 1;
	help = 0;
	if (!ft_strncmp(argv[1], "here_doc", 8))
	{
		argv = here_doc(&argc, argv);
		help = 1;
	}
	check_args(argc, argv, envp);
	get_path(envp);
	data()->cmds = get_commands(argc, argv);
	exec(data()->cmds->next, data()->cmds->fd[0], 
	data()->cmds->next->fd[1], envp);
	while (i < argc - 2)
	{
		wait(NULL);
		i++;
	}
	free_nodes();
	if (help)
		free_matrix(argv);
}
