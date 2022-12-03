/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedperei <pedperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:02:26 by pedperei          #+#    #+#             */
/*   Updated: 2022/11/12 14:50:14 by pedperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*+2 por cuase do \n e do null terminator*/
char	*ft_current_line(char *str)
{
	char	*line;
	int		i;

	line = NULL;
	i = 0;
	if (!(str) || str[i] == '\0')
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		i--;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!(line))
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

/*aloca-se memoria para a string atual (ft_strlen) 
menos a linha que vai ser	retornada(i)*/
char	*ft_next_line(char *str)
{
	char	*new_line;
	char	*temp;
	int		i;

	new_line = NULL;
	temp = NULL;
	if (!(str))
		return (NULL);
	if (ft_strchr_mod(str, '\n') != NULL)
		temp = ft_strchr_mod(str, '\n');
	else
	{
		free(str);
		return (NULL);
	}
	new_line = (char *)malloc(sizeof(char) * (ft_strlen_mod(temp) + 1));
	if (!(new_line))
		return (NULL);
	i = -1;
	while (temp[++i] != '\0')
		new_line[i] = temp[i];
	new_line[i] = '\0';
	free(str);
	return (new_line);
}

/*flag indica o numero de bytes lido - conteudo lido e alocado no buffer*/
/*se der erro fazer free do node e do seu content*/
/* poe se o null terminator num byte a seguir ao conteudo lido 
para se ter uma string terminada em null no buffer*/
/*char pointer text passa a apontar para o content do node*/
/*o content passa a ser a concatenacao entre text(o conteudo atual) 
e a string que esta no buffer*/
/*faz-se free do conteudo antigo - strjoin aloca sempre nova memoria*/
/*quando se encontra uma new line sai-se do loop 
- ja pode ser retornada um linha pelo menos*/
char	*ft_read(int fd, char *buffer, char *list)
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
			free(list);
			list = NULL;
			return (NULL);
		}
		buffer[flag] = '\0';
		text = list;
		list = ft_strjoin(text, buffer);
		free(text);
		if (ft_strchr_mod(buffer, '\n') != NULL)
			break ;
	}
	return (list);
}

/*+1 por causa do byte extra do null*/
/*faz-se read e o texto e posto no content do temp_node*/
/*aloca-se a string de uma linha a um 
ponteiro temporario ao qual se vai fazer return*/
/*atualiza-se o content do node - e tirada a linha 
que vai ser retornada - fica so o que estiver para a frente disso*/
/*free do buffer*/
/*retorna-se a tring com a linha*/
char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*list;
	char		*temp;

	if (fd < 0 || fd > 4096 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(buffer))
		return (NULL);
	list = ft_read(fd, buffer, list);
	temp = ft_current_line(list);
	list = ft_next_line(list);
	free(buffer);
	return (temp);
}
