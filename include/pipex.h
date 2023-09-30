/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:41:00 by soutin            #+#    #+#             */
/*   Updated: 2023/09/28 23:14:50 by soutin           ###   ########.fr       */
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
	int		ac;
	char	**av;
	int		fdi;
	int		fdo;
	int		nb_cmds;
	char	*limiter;
	int		pipe_fd[2];
	int		tmp_fd;
	char	**envp;
	char	**envp_path;
	char	*cmd_path;
	char	**argv;
}			t_vars;

int			init_vars(t_vars *vars, int ac, char **av, char **envp);
char		**init_paths(char **envp);
int			init_cmd_and_files(t_vars *vars, char **av, int i);
int			openfile(t_vars *vars, char **av, int i);
int			init_cmd_path(t_vars *vars);
int			path_to_argv(char **argv);
int			here_doc_loop(t_vars *vars);
char		*cmdjoin(char *path, char *cmd);

int			exec_pipeline(t_vars *vars);
void		in_out_pipe(t_vars *vars, int i);
int			tough_choices(t_vars *vars, int i);

void		freevars(t_vars *vars, int i);
void		freetabs(char **tab);

#endif