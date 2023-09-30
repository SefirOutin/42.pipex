/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 19:07:50 by soutin            #+#    #+#             */
/*   Updated: 2023/09/27 17:08:46 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static char	*ft_join(char *line, char *buffer)
{
	char	*new;
	int		i;
	size_t	len;

	i = 0;
	if (!buffer)
		return (NULL);
	if (line)
		len = ft_strlen(line) + ft_strlen(buffer) + 1;
	else
		len = ft_strlen(buffer) + 1;
	new = ft_calloc(len, sizeof(char));
	if (!new)
		return (NULL);
	if (line)
	{
		ft_strlcpy(new, line, ft_strlen(line));
		ft_strlcat(new, buffer, len);
		free(line);
	}
	else
		ft_strlcpy(new, buffer, len);
	return (new);
}

static int	in_line(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static void	trim_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	line[i] = '\0';
}

static void	trim_buffer(char *buffer, long nb)
{
	int		i;
	int		l;
	char	tmp;

	l = 0;
	i = 0;
	if (!buffer)
		return ;
	while (buffer[i] != '\n' && buffer[i])
		i++;
	while (buffer[++i] && (nb || in_line(buffer)))
	{
		tmp = buffer[i];
		buffer[l] = tmp;
		l++;
	}
	buffer[l] = '\0';
}

char	*get_next_line(int fd)
{
	t_gnl		vars;
	static char	buffer[BUFFER_SIZE + 1];

	vars.nb_bytes = 1;
	if (fd < 0 || read(fd, buffer, 0) < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	vars.line = ft_join(NULL, buffer);
	if (!vars.line)
		return (NULL);
	while (!in_line(vars.line))
	{
		vars.nb_bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[vars.nb_bytes] = '\0';
		if (!vars.nb_bytes)
			break ;
		if (vars.nb_bytes < 0)
			return (free(vars.line), NULL);
		vars.line = ft_join(vars.line, buffer);
		if (!vars.line)
			return (NULL);
	}
	trim_line(vars.line);
	if (!vars.line[0])
		return (free(vars.line), NULL);
	return (trim_buffer(buffer, vars.nb_bytes), vars.line);
}
