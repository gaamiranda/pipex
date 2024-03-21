# include "bonus.h"

void	check_args(int argc, char **argv, char **envp)
{
	if (!(*envp))
	{
		write(2, "No environment variables\n", 25);
		exit(0);
	}
	if (argc < 5)
	{
		write(2, "Invalid argc number\n", 21);
		exit(0);
	}
	(process())->read_fd = open(argv[1], O_RDONLY);
	if (process()->read_fd == -1)
	{
		write(2, "no such file or directory\n", 27);
		exit(0);
	}
	(process())->output_fd = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (process()->output_fd == -1)
	{
		close(process()->read_fd);
		write(2, "Error trying to open/create output file\n", 41);
		exit(0);
	}
}

void	free_matrix(char **matx)
{
	int		i;

	i = 0;
	while (matx[i])
	{
		free(matx[i]);
		i++;
	}
	free(matx);
}

void	ft_error(char *str, t_cmd **head)
{
	int		i;
	t_cmd	*temp;

	temp = *head;
	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	while (temp)
	{
		*head = (*head)->next;
		free_matrix(temp->args);
		free(temp);
		temp = *head;
	}
	exit(1);
}

int		check_bar(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
