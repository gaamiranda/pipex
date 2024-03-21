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

#include "bonus.h"

char	*get_path(char *cmd, char **envp);
static void	free_commands(t_cmd *head);

void	lst_add(t_cmd **head, t_cmd *node)
{
	t_cmd	*temp;

	temp = *head;
	if (!(*head))
	{
		*head = node;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = node;
	}
}

t_cmd	*node_create(char **argv, int i, int argc, t_cmd **head)
{
	t_cmd	*node;

	node = (t_cmd *)malloc(sizeof(t_cmd));
	node->args = ft_split(argv[i], ' ');
	node->fd_in = -1;
	node->fd[0] = 0;
	node->fd[1] = 1;
	node->fd_out = -1;
	node->path = NULL;
	node->next = NULL;
	lst_add(head, node);
	return (node);
}

static t_cmd *create_struct(int argc, char **argv, char **envp)
{
	t_cmd	*new_node;
	t_cmd	*head;
	int		i;

	i = 2;
	head = NULL;
	while (i < argc - 1)
	{
		new_node = node_create(argv, i, argc, &head);
		if (i == 2)
			new_node->fd_in = process()->read_fd;
		else if (i == (argc - 2))
			new_node->fd_out = process()->output_fd;
		new_node->path = get_path(*new_node->args, envp);
		i++;
	}
	return (head);
}
char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	**path;
	char	*temp;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("PATH=", envp[i], 4))
			break;
	}
	path = ft_split(envp[i], ':');
	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], cmd);
		if (!access(temp, X_OK))
		{
			free_array(path);
			return (temp);
		}
		free(temp);
		i++;
	}
	free_array(path);
	return (NULL);
}

void	exec_command(t_cmd	*cmd, char **envp, int in, int out)
{
	if (fork() == 0)
	{
		dup2(in, 0);
		dup2(out, 1);
		if (in != 0)
			close(in);
		if (out != 1)
			close(out);
		if (execve(cmd->path, cmd->args, envp) == -1)
			free_commands(cmd);
		exit(127);
	}
	if (in != 0)
		close(in);
	if (out != 1)
		close(out);
}


void	exec_commands(t_cmd	*head, char **envp)
{
	int		in;
	int		out;

	in = 0;
	while (head)
	{
		if (head->fd_in != -1)
			in = head->fd_in;
		if (head->next && pipe(head->fd) == -1)
			break;
		out = head->fd[1];
		if (head->fd_out != -1)
			out = head->fd_out;
		printf("in: %d out: %d fd_out: %d\n", in, out, head->fd_out);
		exec_command(head, envp, in, out);
		in = head->fd[0];
		head = head->next;
	}
}

static void	free_commands(t_cmd *head)
{
	t_cmd *temp;

	temp = head;
	while (temp)
	{
		wait(NULL);
		head = head->next;
		free_array(temp->args);
		free(temp->path);
		free(temp);
		temp = head;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_cmd	*head;

	check_args(argc, argv, envp);
	head = create_struct(argc, argv, envp);
	exec_commands(head, envp);
	free_commands(head);
}