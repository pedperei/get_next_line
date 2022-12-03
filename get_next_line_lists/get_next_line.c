/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedperei <pedperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:02:26 by pedperei          #+#    #+#             */
/*   Updated: 2022/11/03 01:51:09 by pedperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

static char *ft_current_line(char *str)
{
    char *line;
    int i;

    line = NULL;
    i = 0;
    if (!(str) || str[i] == '\0')
        return (NULL);
    while (str[i] != '\n' && str[i] != '\0')
        i++;
    line = (char *)malloc(sizeof(char) * (i + 2));/*+2 por cuase do \n e do null terminator*/
    if (!(line))
        return NULL;
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

static char *ft_next_line(char *str)
{
    char *new_line;
    int i;
    int j;

    new_line = NULL;
    i = 0;
    j= 0;
    if (!(str))
        return (NULL);
    while (str[i] != '\n' && str[i] != '\0')
        i++;
    if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
    new_line = (char *)malloc(sizeof(char) * (ft_strlen_mod(str) - i));
    if (!(new_line))/*aloca-se memoria para a string atual (ft_strlen) menos a linha que vai ser retornada(i)*/
        return NULL;
    while (str[++i] != '\0')
        new_line[j++] = str[i];
    new_line[j] = '\0';
    free(str);
    return (new_line);
}

static t_list *ft_read(int fd, char *buffer, t_list *list)
{
    int flag;
    char *text;

    flag = 1;
    text = NULL;
    while (flag > 0)
    {
        flag = read(fd,buffer,BUFFER_SIZE);/*flag indica o numero de bytes lido - conteudo lido e alocado no buffer*/
        if (flag == -1) /*se der erro fazer free do node e do seu content*/
        {
            free(list->content);
            free(list);
            return NULL;
        }
        buffer[flag] = '\0';/* poe se o null terminator num byte a seguir ao conteudo lido para se ter uma string terminada em null no buffer*/
        text = list->content; /*char pointer text passa a apontar para o content do node*/
        list->content = ft_strjoin(text,buffer);/*o content passa a ser a concatenacao entre text(o conteudo atual) e a string que esta no buffer*/
        free(text);/*faz-se free do conteudo antigo - strjoin aloca sempre nova memoria*/
        if (ft_strchr(buffer,'\n'))/*quando se encontra uma new line sai-se do loop - ja pode ser retornada um linha pelo menos*/
            break;
    }
    if (flag == 0)/*se o numero de bytes for 0 a flag do node passa a ser 1*/
        list->flag = 1;
    return (list);
}

static t_list *ft_select_list(t_list *list, int fd)
{
    t_list *current_file;

    current_file=list;
    while (current_file != NULL)
    {
        if (fd == current_file->fd)/*quando se encontra o node com o fd atual retorna-se esse node*/
            break;
        current_file = current_file->next;
    }
    return (current_file);
}

static t_list *ft_check_list(t_list *list, int fd)
{
    char *temp;
    t_list *str;

    temp = NULL;
    str = list;
    while (str != NULL)
    {
        if (fd == str->fd)/*quando encontrar o elemento da lista com o fd atual*/
        {
            list = ft_move_end(list,str);/*move esse elemento para o final da lista para depois se poder fazer free*/
            return(list);
        }
        str = str->next;
    }
    str = ft_lstnew(fd, temp);/*se nao existir o fd atual na lista cria um novo node*/
    list = ft_move_end(list,str);/*esse node e movido para o final da lista*/
    return (list);/*retorna-se a lista com as alteracoes*/
}

static t_list *ft_update_list(t_list *list, t_list *temp_node, int fd)
{
    t_list *temp;

    temp = list;
    while (temp != NULL)
    {
        if (fd == temp->fd)
        {
            temp->content = temp_node->content;
            break;
        }
        temp = temp->next;
    }
    return (list);
}

static t_list *ft_check_free(t_list *list, t_list *node, char* line)
{
    t_list *temp;

    temp = list;
    while (temp->next != NULL)
    {
        if(temp->next->flag == 1 && temp->next->fd == node->fd && line == NULL)
        {
            free(temp->next);
            temp->next = NULL;
            return (list);
        }
        temp=temp->next;
    }
    if (list->flag == 1 && list->fd == node->fd && line == NULL)
    {
        free(temp);
        list = NULL;
    }
    return (list);
}

char *get_next_line(int fd)
{
    char *buffer;
    static t_list* list = NULL;
    t_list* temp_node;
    char *temp;

    temp = NULL;
    if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));/*+1 por causa do byte extra do null*/
    if (!(buffer))
        return (NULL);
    list = ft_check_list(list, fd);/*ve se e necessario fazer alteracoes na lista*/
    temp_node = ft_select_list(list, fd);/*selecciona o node com o fd atual e o ponteiro temp passa a apontar para esse node*/
    temp_node = ft_read(fd, buffer, /*list*/temp_node);/*faz-se read e o texto e posto no content do temp_node*/
    temp = ft_current_line(temp_node->content);/*aloca-se a string de uma linha a um ponteiro temporario ao qual se vai fazer return*/
    temp_node->content = ft_next_line(temp_node->content);/*atualiza-se o content do node - e tirada a linha que vai ser retornada - fica so o que estiver para a frente disso*/
    list = ft_update_list(list, temp_node, fd);/*atualiza-se a lista com as alteracoes feitas (static variable)*/
    //temp_node = list;
    free(buffer);/*free do buffer*/
    //if (temp_node->flag == 1 && temp == NULL)/*se o nº de bytes for 0 e já não houver caracteres para retornar pode-se fazer free do node que esta em uso (fd atual)*/
        //free(list);
    list = ft_check_free(list,temp_node, temp);
    return temp;/*retorna-se a tring com a linha*/
}

 
