/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:50:20 by ljustici          #+#    #+#             */
/*   Updated: 2024/03/06 13:17:03 by ljustici         ###   ########.fr       */
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

int	is_invalid_char_in_map(char *line, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (line[i] != 32 && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'E' && line[i] != 'S'
			&& line[i] != 'W' && line[i] != '\n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_all_spaces(char *line)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = ft_strlen(line);
	while (i < n && line[i] != '\n')
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

void	free_struct(t_data *data)
{
	if (data->no)
	{
		free(data->no);
		data->no = NULL;
	}
	if (data->so)
	{
		free(data->so);
		data->so = NULL;
	}
	if (data->we)
	{
		free(data->we);
		data->we = NULL;
	}
	if (data->ea)
	{
		free(data->ea);
		data->ea = NULL;
	}
	if (data->map)
		ft_free_array(data->map);
}
