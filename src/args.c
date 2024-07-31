#include "../include/pipex.h"

void	check_args(int argc, char **argv, char **envp, int help)
{
	if (!envp)
	{
		write(2, "No environment variables\n", 25);
		exit(1);
	}
	if (argc < 5)
	{
		write(2, "Invalid argc\n", 13);
		exit(1);
	}
	data()->fd_in = open(argv[1], O_RDONLY);
	if (data()->fd_in == -1)
	{
		write(1, "no such file or directory: ", 27);
		write(1, argv[1], ft_strlen(argv[1]));
		data()->fd_in = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(data()->fd_in);
		exit(1);
	}
	if (help == 0)
		data()->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		data()->fd_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (data()->fd_out == -1)
	{
		write(1, "Error with outfile\n", 19);
		exit(1);
	}
}
