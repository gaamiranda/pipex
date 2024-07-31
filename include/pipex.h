#ifndef BONUS_H
# define BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_process{
	int					fd[2];
	char				**coms_array;
	struct s_process	*next;
}	t_process;

typedef struct s_data {
	int			fd_in;
	int			fd_out;
	char		*path;
	t_process	*cmds;
}	t_data;

char		**ft_split(char *str, char c);
char		*ft_strjoin(char *s1, char *s2);
t_data	*data(void);
void	check_args(int argc, char **argv, char **envp);
size_t	ft_strlen(char *str);
int	ft_strncmp(char *s1, char *s2, int n);
t_process *new_node(char *str);
void	list_add(t_process **head, t_process *to_add);
char *check_command(char *path, char *cmd);
void	free_nodes();
char **here_doc(int *argc, char **argv);
char	*get_next_line(int fd);
void	free_matrix(char **matrix);
#endif