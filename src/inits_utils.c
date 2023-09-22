/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 22:52:15 by soutin            #+#    #+#             */
/*   Updated: 2023/09/22 17:10:31 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	mallocs(t_vars *vars)
{
	vars->argvs = (char ***)ft_calloc(sizeof(char **), (vars->ac - 2));
	if (!vars->argvs)
		return (perror("calloc argvs"), -1);
	vars->cmd_path = (char **)ft_calloc(sizeof(char *), (vars->ac - 2));
	if (!vars->cmd_path)
		return (perror("calloc cmdp"), -1);
	return (0);
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
			return (perror("split"), -1);
		while (tmp[i + 1])
			i++;
		free(argv[0]);
		argv[0] = ft_substr(tmp[i], 0, ft_strlen(tmp[i]));
		if (!argv[0])
			return (-1);
		freetabs(tmp);
		return (0);
	}
	else
		return (0);
}

char	**init_path(char **envp)
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
