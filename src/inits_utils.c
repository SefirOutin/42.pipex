/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:52:15 by soutin            #+#    #+#             */
/*   Updated: 2023/09/28 23:32:34 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	**init_paths(char **envp)
{
	int		i;
	char	*tmp;
	char	**envp_path;

	i = 0;
	tmp = NULL;
	while (envp[i++])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			tmp = ft_substr(envp[i], 5, ft_strlen(&envp[i][5]));
			if (!tmp)
				return (NULL);
			break ;
		}
	}
	envp_path = ft_split(tmp, ':');
	if (!envp_path)
		return (free(tmp), NULL);
	free(tmp);
	return (envp_path);
}

char	*cmdjoin(char *path, char *cmd)
{
	char	*new;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	new = ft_strjoin(tmp, cmd);
	if (!new)
		return (free(tmp), NULL);
	free(tmp);
	return (new);
}

int	init_vars(t_vars *vars, int ac, char **av, char **envp)
{
	vars->ac = ac;
	vars->av = av;
	vars->fdi = -2;
	vars->fdo = -2;
	vars->limiter = NULL;
	vars->argv = NULL;
	vars->cmd_path = NULL;
	vars->envp_path = NULL;
	vars->envp = envp;
	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		vars->nb_cmds = ac - 4;
		vars->limiter = av[2];
	}
	else
		vars->nb_cmds = ac - 3;
	vars->envp_path = init_paths(envp);
	if (!vars->envp_path)
		return (-1);
	return (0);
}

void	freetabs(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	freevars(t_vars *vars, int i)
{
	if (!ft_strncmp(vars->av[1], "here_doc", 8))
		unlink("here_doc");
	if (vars->envp_path)
		freetabs(vars->envp_path);
	if (vars->argv)
		freetabs(vars->argv);
	if (vars->cmd_path)
		free(vars->cmd_path);
	if (vars->fdi >= 0)
		close(vars->fdi);
	if (vars->fdo >= 0)
		close(vars->fdo);
	if (i >= 0)
	{
		close(vars->pipe_fd[1]);
		close(vars->pipe_fd[0]);
	}
	if (i != 0)
		close(vars->tmp_fd);
}
