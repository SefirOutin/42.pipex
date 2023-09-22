/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soutin <soutin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:44:27 by soutin            #+#    #+#             */
/*   Updated: 2023/09/22 18:22:55 by soutin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;

	s_len = ft_strlen(src);
	if (!size)
		return (s_len);
	d_len = ft_strlen(dst);
	i = 0;
	if (d_len < size - 1 && size > 0)
	{
		while (src[i] && d_len + i < size - 1)
		{
			dst[d_len + i] = src[i];
			i++;
		}
		dst[d_len + i] = 0;
	}
	if (d_len >= size)
		d_len = size;
	return (d_len + s_len);
}
