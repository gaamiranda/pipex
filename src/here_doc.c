#include "../include/pipex.h"

static int better_strncmp(char *s1, char *s2, int n)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	if (s1[i] == '\n')
		return s2[i] == '\0';
	return 0;
}

static char *ft_strdup(char *s1)
{
    int i;
    char    *ptr;
    int size;

    i = 0;
    size = ft_strlen(s1);
    ptr = ((char*)malloc(sizeof(char) * size + 1));
    if (ptr == NULL)
        return (NULL);
    while (s1[i])
    {
        ptr[i] = s1[i];
        i++;
    }
    ptr[i] = '\0';
    return(ptr);
}

static char **new_argv(int argc, char **argv)
{
	int i;
	char **new;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (argc + 1));
	if (!new)
		return NULL;
	while(argv[i])
	{
		if (i == argc)
			break;
		if (i == 1)
			new[i] = ft_strdup("/tmp/temp_in");
		else if (i >= 2)
			new[i] = ft_strdup(argv[i + 1]);
		else
			new[i] = ft_strdup(argv[i]);
		i++;
	}
	new[argc] = NULL;
	return new;
}

char **here_doc(int *argc, char **argv)
{
	char *temp;
	int	fd;

	temp = NULL;
	fd = open("/tmp/temp_in", O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		write(1, "Could not create file in tmp\n", 29);
		exit(1);
	}
	while (1)
	{
		temp = get_next_line(STDIN_FILENO);
		if (!temp || better_strncmp(temp, argv[2], ft_strlen(argv[2])))
			break;
		write(fd, temp, ft_strlen(temp));
		free(temp);
		temp = NULL;
	}
	free(temp);
	*argc -= 1;
	close(fd);
	return (new_argv(*argc, argv));
}
