/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljustici <ljustici@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:25:13 by ljustici          #+#    #+#             */
/*   Updated: 2024/02/28 14:41:15 by ljustici         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*set_after_nl(char *has_nl)
{
	int		i;
	int		n;
	char	*after_nl;

	i = 0;
	while (has_nl[i] && has_nl[i] != '\n')
		i++;
	if (!has_nl[i])
	{
		free(has_nl);
		return (NULL);
	}
	after_nl = (char *)malloc((ft_strlen(has_nl) - i + 1) * sizeof(char));
	if (!after_nl)
		return (free(has_nl), NULL);
	i++;
	n = 0;
	while (has_nl[i])
		after_nl[n++] = has_nl[i++];
	after_nl[n] = '\0';
	free(has_nl);
	return (after_nl);
}

char	*get_before_nl(char *has_nl)
{
	char	*before_nl;
	int		i;

	i = 0;
	if (!has_nl[i])
		return (NULL);
	while (has_nl[i] && has_nl[i] != '\n')
		i++;
	if (ft_strrchr(has_nl, '\n'))
		i++;
	before_nl = (char *)malloc((i + 1) * sizeof(char));
	if (!before_nl)
		return (NULL);
	before_nl[i] = '\0';
	while (i > 0)
	{
		--i;
		before_nl[i] = has_nl[i];
	}
	return (before_nl);
}

char	*ft_join_ffree(char *s1, char *s2)
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

char	*get_buffer(int fd, char *has_nl)
{
	ssize_t	n_read_bytes;
	char	*buffer;

	n_read_bytes = 1;
	buffer = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (NULL);
	while (n_read_bytes != 0 && !ft_strrchr(has_nl, '\n'))
	{
		n_read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_read_bytes <= -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[n_read_bytes] = '\0';
		has_nl = ft_join_ffree(has_nl, buffer);
	}
	free(buffer);
	return (has_nl);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*has_nl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	has_nl = get_buffer(fd, has_nl);
	if (!has_nl)
		return(NULL);
	line = get_before_nl(has_nl);
	has_nl = set_after_nl(has_nl);
	return (line);
}

/*#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*buffer;

	buffer ="a";
	fd = open("./multiple_line_no_nl", O_RDONLY);
	while (buffer)
	{
		
		buffer = get_next_line(fd);	
		printf("\nlinea que llega al main: [ %s ]", buffer);
		free(buffer);
	}
	close(fd);
	system("leaks a.out");
	return (0);
}
 */
