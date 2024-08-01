#include "../include/pipex.h"


size_t	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while(str[i])
		i++;
	return i;
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	return s1[i] - s2[i];
}

void	free_matrix(char **matrix)
{
	int		i;

	i = -1;
	if(!matrix)
		return ;
	while(matrix[++i])
		free(matrix[i]);
	free(matrix);
}

char *check_command(char *path, char *cmd)
{
	int		i;
	char	**env_possible;
	char	*temp;
	char	*hold;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return ft_strjoin("", cmd);
	env_possible = ft_split(path, ':');
	hold = ft_strjoin(env_possible[i], cmd);
	while(env_possible[i])
	{
		temp = ft_strjoin(env_possible[i], cmd);
		if (access(temp, X_OK) == 0)
		{
			free_matrix(env_possible);
			free(hold);
			return temp;
		}
		free(temp);
		i++;
	}
	free_matrix(env_possible);
	return hold;
}

void	free_nodes()
{
	t_process *temp;
	t_process *head;

	head = data()->cmds;
	while (head)
	{
		temp = head;
		if (temp->coms_array)
			free_matrix(temp->coms_array);
		head = temp->next;
		free(temp);
	}
}
