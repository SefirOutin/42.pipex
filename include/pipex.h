/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:41:00 by soutin            #+#    #+#             */
/*   Updated: 2023/09/22 17:32:20 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_vars
{
	int		fdi;
	int		fdo;
	char	*limiter;
	int		ac;
	int		error;
	int		pipe_fd[2];
	int		tmp_fd;
	char	**envp;
	char	**envp_path;
	int		pids[1024];
	int		nb_steps;
	char	**cmd_path;
	char	***argvs;
}			t_vars;

int			parse(t_vars *vars, int ac, char **av);
char		**init_path(char **envp);
int			init_vars(t_vars *vars, int ac);
int			init_cmd(t_vars *vars, char **av);
int			init_cmd_path(t_vars *vars, int index);
int			openfiles(t_vars *vars, char **av);
int			mallocs(t_vars *vars);
int			path_to_argv(char **argv);
int			here_doc_loop(t_vars *vars);

int			exec_pipeline(t_vars *vars);

int			cmd_process(t_vars *vars, char **argv);

char		*cmdjoin(char *path, char *cmd);

void		freevars(t_vars *vars);
void		freetabs(char **tab);
void		tabs_print(char ***tab);
void		tab_print(char **tab);

#endif