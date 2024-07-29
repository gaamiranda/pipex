#include "../include/pipex.h"

t_process *new_node(char *str)
{
	t_process *new;

	new = malloc(sizeof(t_process));
	if (!new)
		return NULL;
	new->fd[0] = -1;
	new->fd[1] = -1;
	new->next = NULL;
	new->coms_array = ft_split(str, ' ');
	return new;
}


void	list_add(t_process **head, t_process *to_add)
{
	t_process *temp;

	temp = NULL;
	if (!(*head))
	{
		*head = to_add;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = to_add;
}