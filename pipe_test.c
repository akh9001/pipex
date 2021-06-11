/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalidy <akhalidy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 19:33:59 by akhalidy          #+#    #+#             */
/*   Updated: 2021/06/11 19:41:18 by akhalidy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int fd[2];
    int arr[]= {5, 2, 9, 6, 0, 9, 6 ,4, 23};
    int end;
    int start;
    int sum;

    sum = 0;
    if (pipe(fd) == -1)
    {
        printf("An error occured with openning the pipe\n");
        return(1);
    }
    int id;
    if ((id = fork()) == -1)
    {
        printf(" An Error occured with the fork\n");
        return(2);
    }
    if (!id)
    {
        close(fd[0]);
        start = 0;
        end = (sizeof(arr) / sizeof(int)) / 2;
        for (int i= start; i < end; i++)
            sum += arr[i];
        write(fd[1], &sum, sizeof(int));
        write(fd[1], "hey, this is Asmaa\n", sizeof("hey, this is Asmaa\n"));
        close(fd[1]);
        printf("Child sub sum : %d\n", sum);
        printf("Child has finished his work!\n");
    }
    else
    {
        int total;
        char *str;
        str = (char *)malloc(20);
        close(fd[1]);
				// sizeof returns the size in bytes so we should 
				// divide it by the size of int!
        start = (sizeof(arr) / sizeof(int)) / 2;
        end = sizeof(arr) / sizeof(int);
        printf("size of the arr : %d\nstart : %d\n", end, start);
        for (int i= start; i < end; i++)
            sum += arr[i];
        printf("Parent sub sum : %d\n", sum);
        read(fd[0], &total, sizeof(int));
        read(fd[0], str, 20);
        printf("%s", str);
		close(fd[0]);
        sum += total;
        wait(NULL);
        printf("Sum equals : %d\n", sum);
    }
    return(0);
}