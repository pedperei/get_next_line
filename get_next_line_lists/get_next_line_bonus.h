/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedperei <pedperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 19:43:37 by pedperei          #+#    #+#             */
/*   Updated: 2022/11/02 17:30:07 by pedperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
#include <stdio.h>
#include <stdlib.h>

char *get_next_line(int fd);
size_t	ft_strlen_mod(const char *s);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memset(void *ptr, int x, size_t n);

typedef struct s_list
{
	void			*content;
	int fd;
	int flag;
	struct s_list	*next;

}	t_list;

t_list	*ft_lstnew(int fd, void *content);
int	ft_lstsize(t_list *lst);
t_list	*ft_lstadd_back(t_list **lst, t_list *new);
t_list* ft_move_end(t_list* list , t_list* node_move) ;

#endif
