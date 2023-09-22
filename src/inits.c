/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:20:32 by soutin            #+#    #+#             */
/*   Updated: 2023/09/22 18:23:11 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	parse(t_vars *vars, int ac, char **av)
{
	if (init_vars(vars, ac) < 0)
		return (-1);
	if (openfiles(vars, av) < 0)
		return (-1);
	if (vars->limiter)
	{
		vars->nb_steps = ac - 4;
		if (here_doc_loop(vars) < 0)
			return (-1);
		open("here_doc", O_RDONLY);
	}
	else
		vars->nb_steps = ac - 3;
	if (init_cmd(vars, av) < 0)
		return (-1);
	freetabs(vars->envp_path);
	vars->envp_path = NULL;
	if (vars->error)
		return (-1);
	return (0);
}

int	init_vars(t_vars *vars, int ac)
{
	vars->ac = ac;
	vars->fdi = 0;
	vars->fdo = 0;
	vars->error = 0;
	vars->limiter = NULL;
	vars->argvs = NULL;
	vars->cmd_path = NULL;
	vars->envp_path = init_path(vars->envp);
	if (!vars->envp_path)
		return (-1);
	return (0);
}

int	init_cmd_path(t_vars *vars, int index)
{
	int	i;

	i = 0;
	while (vars->envp_path[i])
	{
		errno = 0;
		if (vars->cmd_path[index])
			free(vars->cmd_path[index]);
		vars->cmd_path[index] = cmdjoin(vars->envp_path[i],
				vars->argvs[index][0]);
		if (!vars->cmd_path[index])
			return (perror("join"), -1);
		if (access(vars->cmd_path[index], F_OK | X_OK) == 0)
			return (0);
		i++;
	}
	return (ft_printf("command not found: %s\n", vars->argvs[index][0]),
			vars->error++);
}

int	init_cmd(t_vars *vars, char **av)
{
	int	i;
	int	j;

	j = 0;
	i = 2;
	if (vars->limiter)
		i++;
	if (mallocs(vars) < 0)
		return (-1);
	while (av[i + 1])
	{
		vars->argvs[j] = ft_split(av[i], ' ');
		if (!vars->argvs[j])
			return (perror("split"), -1);
		if (path_to_argv(vars->argvs[j]) < 0)
			return (-1);
		else if (init_cmd_path(vars, j) < 0)
			return (-1);
		i++;
		j++;
	}
	vars->argvs[j] = NULL;
	vars->cmd_path[j] = NULL;
	return (0);
}

int	openfiles(t_vars *vars, char **av)
{
	int	i;

	i = 0;
	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		vars->fdi = open(av[1], O_RDWR | O_CREAT, 0664);
		vars->limiter = av[2];
	}
	else
		vars->fdi = open(av[1], O_RDONLY);
	if (vars->fdi < 0)
		return (ft_printf("%s : %s", strerror(errno), av[1]),
			vars->error++);
	while (av[i + 1])
		i++;
	vars->fdo = open(av[i], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (vars->fdo < 0)
		return (ft_printf("%s : %s", strerror(errno), av[i]), vars->error++);
	return (0);
}
