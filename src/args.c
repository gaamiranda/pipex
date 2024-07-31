#include "../include/pipex.h"

static void	write_exit(t_errors err)
{
	if (err == 0)
		write(2, "No environment variables\n", 25);
	else if (err == 1)
		write(2, "Invalid argc\n", 13);
	else if (err == 2)
		write(2, "Error with outfile\n", 19);
	exit(1);
}

void	check_args(int argc, char **argv, char **envp, int help)
{
	if (!(*envp))
		write_exit(NOENV);
	if (argc < 5)
		write_exit(INVALIDARGC);
	data()->fd_in = open(argv[1], O_RDONLY);
	if (data()->fd_in == -1)
	{
		write(2, "no such file or directory: ", 27);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
		data()->fd_in = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		close(data()->fd_in);
		exit(1);
	}
	if (help == 0)
		data()->fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		data()->fd_out = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (data()->fd_out == -1)
		write_exit(ERROROUTFILE);
}
