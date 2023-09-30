/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:20:32 by soutin            #+#    #+#             */
/*   Updated: 2023/09/28 23:43:31 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	init_cmd_path(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->envp_path[i])
	{
		if (vars->cmd_path)
			free(vars->cmd_path);
		vars->cmd_path = cmdjoin(vars->envp_path[i], vars->argv[0]);
		if (!vars->cmd_path)
			return (perror("join"), -1);
		if (access(vars->cmd_path, F_OK | X_OK) == 0)
			return (0);
		i++;
	}
	ft_printf("command not found: %s\n", vars->argv[0]);
	return (-1);
}

int	path_to_argv(char **argv)
{
	char	**tmp;
	int		i;

	i = 0;
	if (!access(argv[0], F_OK | X_OK))
	{
		tmp = ft_split(argv[0], '/');
		if (!tmp)
			return (-1);
		while (tmp[i + 1])
			i++;
		free(argv[0]);
		argv[0] = ft_substr(tmp[i], 0, ft_strlen(tmp[i]));
		freetabs(tmp);
		if (!argv[0])
			return (-1);
		return (0);
	}
	else
		return (0);
}

int	here_doc_loop(t_vars *vars)
{
	char	*buf;
	int		fd;

	buf = NULL;
	fd = open(vars->av[1], O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd < 0)
		return (ft_printf("%s: %s\n", strerror(errno),
				vars->av[1]), -1);
	vars->limiter = ft_strjoin(vars->av[2], "\n");
	if (!vars->limiter)
		return (-1);
	while (1)
	{
		buf = get_next_line(STDIN_FILENO);
		if (!buf)
			return (free(vars->limiter), close(fd), -1);
		ft_putstr_fd(buf, fd);
		if (!ft_strncmp(buf, vars->limiter, ft_strlen(vars->limiter)))
			break ;
		free(buf);
	}
	ft_putstr_fd(NULL, fd);
	free(buf);
	close(fd);
	return (0);
}

int	openfile(t_vars *vars, char **av, int i)
{
	int	j;

	j = 0;
	if (!i)
	{
		if (!ft_strncmp(av[1], "here_doc", 8))
		{
			if (here_doc_loop(vars) < 0)
				return (-1);
			vars->fdi = open(av[1], O_RDONLY);
		}
		else
			vars->fdi = open(av[1], O_RDONLY);
		if (vars->fdi < 0)
			return (ft_printf("%s : %s\n", strerror(errno), av[1]), -1);
	}
	else if (i == vars->nb_cmds - 1 && vars->ac > 4)
	{
		while (av[j + 1])
			j++;
		vars->fdo = open(av[j], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		if (vars->fdo < 0)
			vars->fdo = -2;
	}
	return (0);
}

int	init_cmd_and_files(t_vars *vars, char **av, int i)
{
	if (openfile(vars, vars->av, i) < 0)
		return (freevars(vars, i), -1);
	if (vars->nb_cmds == vars->ac - 3)
		vars->argv = ft_split(av[i + 2], ' ');
	else
		vars->argv = ft_split(av[i + 3], ' ');
	if (!vars->argv)
		return (freevars(vars, i), -1);
	if (path_to_argv(vars->argv) < 0)
		return (freevars(vars, i), -1);
	else if (init_cmd_path(vars) < 0)
		return (freevars(vars, i), -1);
	return (0);
}
