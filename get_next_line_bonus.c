/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzi-xian <lzi-xian@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:21:22 by lzi-xian          #+#    #+#             */
/*   Updated: 2022/10/25 14:33:48 by lzi-xian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(char *h)
{
	int		i;
	char	*p;

	i = 0;
	while (h[i])
		i++;
	p = (char *) ft_calloc(sizeof(char) * (i + 1));
	i = -1;
	while (h[++i])
		p[i] = h[i];
	p[i] = '\0';
	free(h);
	return (p);
}

char	*ft_chkstatic(char *h)
{
	char	*p;

	if (!h)
		p = (char *) ft_calloc(1);
	else
		p = ft_strdup(h);
	return (p);
}

char	*ft_read(int fd, char *h)
{
	int		r;
	char	*c;
	char	*p;

	p = ft_chkstatic(h);
	c = (char *) ft_calloc(sizeof(char) * (BUFFER_SIZE + 1));
	r = 1;
	while (r > 0)
	{
		r = read(fd, c, BUFFER_SIZE);
		if (r == 0)
			break ;
		if (r == -1)
		{
			free(c);
			return (NULL);
		}
		c[r] = 0;
		p = ft_strjoin(p, c);
		if (ft_chkstr(p) == 1)
			break ;
	}
	free(c);
	return (p);
}

char	*get_next_line(int fd)
{
	char		*s;
	char		*l;
	static char	*h[8192];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	s = NULL;
	s = ft_read(fd, h[fd]);
	if (!*s)
	{
		free(s);
		h[fd] = NULL;
		return (NULL);
	}
	l = ft_line(s);
	h[fd] = ft_strchr(s);
	return (l);
}
