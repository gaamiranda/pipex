/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gandre-d <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 18:29:48 by gandre-d          #+#    #+#             */
/*   Updated: 2024/03/12 18:29:49 by gandre-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_strdup(const char *s1)
{
    int		i;
    char	*ptr;
    int		size;

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

int	ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	free_array(char **arr)
{
	int		i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

t_process	*process(void)
{
	static t_process	process;

	return (&process);
}

void	close_exit(void)
{
	close(process()->fd[0]);
	close(process()->fd[1]);
	close(process()->output_fd);
	close(process()->read_fd);
	exit(0);
}
