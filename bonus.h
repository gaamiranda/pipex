#ifndef BONUS_H
# define BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_process{
	int		read_fd;
	int		output_fd;
}	t_process;

typedef struct s_cmd {
	char			*path;
	char			**args;
	int				fd_in;
	int				fd_out;
	int				fd[2];
	struct s_cmd	*next;
}	t_cmd;

char		**ft_split(char *str, char c);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_strncmp(char *s1, char *s2, int n);
int			ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
void		free_array(char **arr);
t_process	*process(void);
void		close_exit(void);
void		check_args(int argc, char **argv, char **envp);
void	ft_error(char *str, t_cmd **head);
int		check_bar(char *str);

#endif