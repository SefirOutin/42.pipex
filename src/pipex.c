/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:13:52 by soutin            #+#    #+#             */
/*   Updated: 2023/09/22 18:28:39 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	wait_childs(t_vars *vars)
{
	int	i;
	int	status;

	i = 0;
	while (i < vars->nb_steps)
	{
		if (waitpid(vars->pids[i], &status, 0) < 0)
			return (-1);
		i++;
	}
	return (0);
}

int	in_out_pipe(t_vars *vars, int i)
{
	if (i == 0)
		if (dup2(vars->fdi, STDIN_FILENO) < 0)
			return (perror("dup2"), -1);
	if (i != 0)
		if (dup2(vars->tmp_fd, STDIN_FILENO) < 0)
			return (perror("dup2"), -1);
	if (i != vars->nb_steps - 1)
		if (dup2(vars->pipe_fd[1], STDOUT_FILENO) < 0)
			return (perror("dup2"), -1);
	if (i == vars->nb_steps - 1)
		if (dup2(vars->fdo, STDOUT_FILENO) < 0)
			return (perror("dup2"), -1);
	if (close(vars->pipe_fd[0]) < 0)
		return (perror("close"), -1);
	if (close(vars->pipe_fd[1]) < 0)
		return (perror("close"), -1);
	if (execve(vars->cmd_path[i], vars->argvs[i], vars->envp) < 0)
		return (perror("execve"), -1);
	return (0);
}

int	exec_pipeline(t_vars *vars)
{
	int	i;
	int	status;

	i = 0;
	while (i < vars->nb_steps)
	{
		if (pipe(vars->pipe_fd) < 0)
			return (perror("pipe"), -1);
		vars->pids[i] = fork();
		if (vars->pids[i] < 0)
			return (perror("Fork"), -1);
		if (!vars->pids[i])
		{
			if (in_out_pipe(vars, i) < 0)
				return (-1);
		}
		else
			if (waitpid(vars->pids[i], &status, 0) < 0)
				return (-1);
		if (close(vars->pipe_fd[1]) < 0)
			return (-1);
		vars->tmp_fd = vars->pipe_fd[0];
		i++;
	}
	if (close(vars->tmp_fd) < 0)
		return (-1);
	// if (wait_childs(vars) < 0)
	// 	return (-1);
	return (0);
}
