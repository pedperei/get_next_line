/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedperei <pedperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:02:26 by pedperei          #+#    #+#             */
/*   Updated: 2022/11/12 14:50:10 by pedperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*+2 por causa do \n e do null terminator*/
char	*ft_current_line(int fd, char **str)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	if (!(str[fd]) || str[fd][i] == '\0')
		return (NULL);
	while (str[fd][i] != '\n' && str[fd][i] != '\0')
		i++;
	if (str[fd][i] == '\0')
		i--;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!(line))
		return (NULL);
	i = 0;
	while (str[fd][i] != '\n' && str[fd][i] != '\0')
	{
		line[i] = str[fd][i];
		i++;
	}
	if (str[fd][i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

/*aloca-se memoria para a string atual (ft_strlen) 
menos a linha que vai ser	retornada(i)*/
char	*ft_next_line(int fd, char **str)
{
	char	*new_line;
	char	*temp;
	int		i;

	new_line = NULL;
	temp = NULL;
	if (!(str[fd]))
		return (NULL);
	if (ft_strchr_mod(str[fd], '\n') != NULL)
		temp = ft_strchr_mod(str[fd], '\n');
	else
	{
		free(str[fd]);
		return (NULL);
	}
	new_line = (char *)malloc(sizeof(char) * (ft_strlen_mod(temp) + 1));
	if (!(new_line))
		return (NULL);
	i = -1;
	while (temp[++i] != '\0')
		new_line[i] = temp[i];
	new_line[i] = '\0';
	free(str[fd]);
	return (new_line);
}

/*flag indica o numero de bytes lido
- conteudo lido e alocado no buffer*/
/*se der erro fazer free do node e do seu content*/
/* poe se o null terminator num byte a seguir ao conteudo lido 
para se ter uma string terminada em null no buffer*/
/*char pointer text passa a apontar para o content do node*/
/*o content passa a ser a concatenacao entre text(o conteudo atual) 
e a string que esta no buffer*/
/*faz-se free do conteudo antigo- strjoin aloca sempre nova memoria*/
/*quando se encontra uma new line sai-se do loop
- ja pode ser retornada um linha pelo menos*/
char	*ft_read(int fd, char *buffer, char **list)
{
	int		flag;
	char	*text;

	flag = 1;
	text = NULL;
	while (flag > 0)
	{
		flag = read(fd, buffer, BUFFER_SIZE);
		if (flag == -1)
		{
			free(list[fd]);
			return (NULL);
		}
		buffer[flag] = '\0';
		text = (list[fd]);
		list[fd] = ft_strjoin(text, buffer);
		free(text);
		if (ft_strchr_mod(buffer, '\n') != NULL)
			break ;
	}
	return (list[fd]);
}

/*+1 por causa do byte extra do null*/
/*faz-se read e o texto e posto no content do temp_node*/
/*aloca-se a string de uma linha a um ponteiro temporario 
ao qual se vai fazer return*/
/*atualiza-se o content do node- e tirada a linha que vai ser retornada
- fica so o que estiver para a frente disso*/
/*free do buffer*/
/*retorna-se a tring com a linha*/
char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*list[4096];
	char		*temp;

	if (fd < 0 || fd > 4096 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(buffer))
		return (NULL);
	list[fd] = ft_read(fd, buffer, list);
	temp = ft_current_line(fd, list);
	list[fd] = ft_next_line(fd, list);
	free(buffer);
	return (temp);
}
