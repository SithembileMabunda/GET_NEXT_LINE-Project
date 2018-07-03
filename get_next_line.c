/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smabunda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 15:25:05 by smabunda          #+#    #+#             */
/*   Updated: 2018/07/02 14:24:12 by smabunda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft/libft.h"

static int		reading(const int fd, char **line)
{
	char		*buff;
	char		*str;
	int			bytes;

	buff = ft_strnew(sizeof(*buff) * (BUFF_SIZE + 1));
	if (!buff)
		return (-1);
	bytes = read(fd, buff, BUFF_SIZE);
	if (bytes > 0)
	{
		buff[bytes] = '\0';
		str = ft_strjoin(*line, buff);
		if (!(str))
			return (-1);
		free(*line);
		*line = str;
	}
	if (buff)
		free(buff);
	return (bytes);
}

int				get_next_line(const int fd, char **line)
{
	int			red;
	char		*nl;
	static char	*str;

	if (!line || (!str && (str = ft_strnew(sizeof(*str))) == NULL))
		return (-1);
	nl = ft_strchr(str, '\n');
	while (nl == NULL)
	{
		if ((red = reading(fd, &str)) == 0)
		{
			if (ft_strlen(str) == 0)
				return (0);
			str = ft_strjoin(str, "\n");
		}
		if (red < 0)
			return (-1);
		else
			nl = ft_strchr(str, '\n');
	}
	*line = ft_strsub(str, 0, ft_strlen(str) - ft_strlen(nl));
	nl = ft_strdup(nl + 1);
	free(str);
	str = nl;
	return (1);
}
