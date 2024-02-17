/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:50:20 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/17 18:42:00 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_join_free(char *s1, char *s2)
{
	char	*s;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	s = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(*s));
	if (!s)
		return (NULL);
	i = 0;
	j = -1;
	if (s1)
	{
		while (s1[i])
		{
			s[i] = s1[i];
			i++;
		}
		free(s1);
	}
	while (s2[++j])
		s[i++] = s2[j];
	return (s);
}

int	ft_array_len(char **str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
