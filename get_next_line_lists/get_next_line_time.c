/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_time.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedperei <pedperei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 23:02:26 by pedperei          #+#    #+#             */
/*   Updated: 2022/10/09 21:43:09 by pedperei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>

char *ft_current_line(char *str)
{
    char *line;
    int i;

    line = NULL;
    i = 0;
    if (!(str) || str[i] == '\0')
        return (NULL);
    while (str[i] != '\n' && str[i] != '\0')
        i++;
    line = (char *)malloc(sizeof(char) * (i + 2));
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

char *ft_next_line(char *str)
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
    new_line = (char *)malloc(sizeof(char) * (ft_strlen(str) - i));
    if (!(new_line))
        return NULL;
    while (str[++i] != '\0')
        new_line[j++] = str[i];
    new_line[j] = '\0';
    free(str);
    return (new_line);
}

char *ft_read(int fd, char *buffer, char *str)
{
    int flag;
    char *text;

    flag = 1;
    text = NULL;
    while (flag > 0)
    {
        flag = read(fd,buffer,BUFFER_SIZE);
        if (flag == -1)
        {
            free(buffer);
            free(str);
            return NULL;
        }
        buffer[flag] = '\0';
        text = str;
        str = ft_strjoin(text,buffer);
        free(text);
        if (ft_strchr(buffer,'\n'))
            break;
    }
    return (str);
}

char *get_next_line(int fd)
{
    char *buffer;
    static char *str = NULL;
    char *temp;

    if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
    buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!(buffer))
        return (NULL);
    str = ft_read(fd, buffer, str);
    temp = ft_current_line(str);
    str = ft_next_line(str);
    free(buffer);
    return temp;
}

/*int	main(int argc, char **argv)
{
	int	fd;
    int	fd2;
	char	*line;

	(void)argc;			// Casting argc to quiet the compiler's warnings.
	fd = open("files/empty", O_RDWR);
    printf("%d", fd);
    //fd2 = open("test2.txt", O_RDONLY);
    //fd = -5; 	// Open the file given as an argument at program launch
	line = "";			// Initialize this variable to be able to use it in the following loop
	while (line != NULL)
	{
		line = get_next_line(fd);
        //line2 = get_next_line(fd2);
        if (line != NULL)
		    printf("%s", line);	// We're omitting any \n in this printf because get_next_line is supposed to include the \n for each line
	    //if (line2 != NULL)
		    //printf("%s", line2);	// We're omitting any \n in this printf because get_next_line is supposed to include the \n for each line

    }
	fd = close(fd);
	return (0);
}  */


/* int main(int argc, char *argv[])
{
    int fd;
    char* c1;
    char* c2;
    //printf("%s\n",argv[1]);
    fd = open("test.txt",O_RDONLY);
    //printf("%d\n",fd);
    c1 = get_next_line(fd);
    printf("%s",c1);
    //c2 = get_next_line(fd);
    //printf("%s",c2);
    //printf("%s",get_next_line(fd));
    //printf("%s",get_next_line(fd));
    //printf("%s",get_next_line(fd));
    //printf("%s",get_next_line(fd));
    close(fd);
}  */