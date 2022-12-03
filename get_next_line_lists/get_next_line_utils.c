/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedperei <pedperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:39:07 by pedperei          #+#    #+#             */
/*   Updated: 2022/11/03 00:47:40 by pedperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"


size_t	ft_strlen_mod(const char *s)
{
	size_t	i;

	i = 0;
	while (s != NULL && s[i] != '\0')
	{
		i++;
	}
	return (i);
}


char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
		{
			return ((char *)&str[i]);
		}
		i++;
	}
	if ((char)c == str[i])
	{
		return ((char *)&str[i]);
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*strjoin;
	int		len;

	i = 0;
	j = 0;
	
	len = ft_strlen_mod(s1) + ft_strlen_mod(s2);
	strjoin = (char *)malloc(sizeof(char) * (len + 1));
	if (strjoin == NULL)
		return (NULL);
	while (s1 != NULL && s1[i] != '\0')
	{
		strjoin[i] = s1[i];
		i++;
	}
	while (s2 != NULL && s2[j] != '\0')
	{
		strjoin[i + j] = s2[j];
		j++;
	}
	strjoin[i + j] = '\0';
	return (strjoin);
}


void	*ft_memset(void *ptr, int x, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char *)ptr;
	while (i < n)
	{
		temp[i] = x;
		i++;
	}
	return (ptr);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	temp = *lst;
	while ((*lst) != NULL)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
}

t_list	*ft_lstnew(int fd, void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	new->fd = fd;
	new->flag = 0;
	new->content = content;
	new->next = NULL;
	return (new);
}

int	ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		i;

	temp = lst;
	i = 1;
	if (lst == NULL)
		return (0);
	while (temp->next != NULL)
	{
		temp = temp->next;
		i ++;
	}
	return (i);
}

t_list	*ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (temp == NULL)
		*lst = new;
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new;
	}
	return (*lst);
}

/*verifica se já existe algum elemento da lista com o mesmo fd*/
int check_node(t_list* list , int fd)
{
	while (list != NULL) 
	{
        if (list->fd == fd)
            return (1);
        list = list->next;
    }
	return (0);
}

t_list* ft_move_end(t_list* list , t_list* node_move) 
{
	t_list *temp;
	temp = list;
	if (list == NULL)
	{
		list = node_move;
		return (list);
	}
	if (check_node(list, node_move->fd) == 1 && node_move->next == NULL)
		return (list);
	if (check_node(list, node_move->fd) == 0)
		return (ft_lstadd_back(&list, node_move));
	if (temp->fd == node_move->fd) /*se o primeiro elemento da lisa coincidir o fd avanca-se para a frente (passando a lista a comecar nesse elemneto)*/
        list = list->next;
    while (temp->next != NULL) 
	{
        if (temp->next->fd == node_move->fd) /* se o elemnto a seguir tiver o fd igual ao node em comparacao*/
            temp->next = temp->next->next; /*o next passa a apontar para dois nodes a frente ()*/
        temp = temp->next;
    }
    temp->next = node_move;
    node_move->next = NULL;
    return (list);
}
