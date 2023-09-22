/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:40:39 by soutin            #+#    #+#             */
/*   Updated: 2023/09/22 17:44:25 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	tabs_print(char ***tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i][0]);
		ft_printf("%s\n", tab[i][1]);
		i++;
	}
}

void	tab_print(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

int	here_doc_loop(t_vars *vars)
{
	char	*buf;

	buf = NULL;
	while (1)
	{
		if (buf)
			free(buf);
		buf = get_next_line(STDIN_FILENO);
		if (!buf)
			return (free(buf), -1);
		ft_putstr_fd(buf, vars->fdi);
		if (!ft_strncmp(buf, vars->limiter, ft_strlen(vars->limiter)))
			break ;
	}
	free(buf);
	close(vars->fdi);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_vars	vars;

	vars.envp = envp;
	if (ac <= 1027)
	{
		if (parse(&vars, ac, av) < 0)
			return (freevars(&vars), 1);
		exec_pipeline(&vars);
		freevars(&vars);
		close(vars.pipe_fd[0]);
	}
	else
		ft_printf("parse error near \"|\" ");
	return (0);
}
