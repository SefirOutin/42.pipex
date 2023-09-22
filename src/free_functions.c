/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 19:21:28 by soutin            #+#    #+#             */
/*   Updated: 2023/09/22 18:23:41 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

void	freevars(t_vars *vars)
{
	int	i;

	i = 0;
	if (vars->envp_path)
		freetabs(vars->envp_path);
	if (vars->argvs)
	{
		while (vars->argvs[i])
		{
			freetabs(vars->argvs[i]);
			i++;
		}
		free(vars->argvs);
	}
	if (vars->cmd_path)
		freetabs(vars->cmd_path);
}
