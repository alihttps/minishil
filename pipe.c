#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int find_pipe_index(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
        if (strcmp(av[i], "|") == 0)
        {
            return i;
        }
    }
    return -1;
}

void pipe_and_execute(char **cmd1, char **cmd2, char **env)
{
    int fd[2];
    pid_t id1, id2;
    // int status;
    
    if (pipe(fd) == -1)
    {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    id1 = fork();
    if (id1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO); 
        close(fd[0]);               
        close(fd[1]);

        execve(cmd1[0], cmd1, env);
        perror ("cant execute cmd2");
        exit(EXIT_FAILURE);
    }

    id2 = fork();
    if (id2 == 0)
    {
        dup2(fd[0], STDIN_FILENO);   
        close(fd[1]);       
        close(fd[0]);

        execve(cmd2[0], cmd2, env);
        perror ("cant execute cmd2");
        exit(EXIT_FAILURE);
    }

    close(fd[0]);
    close(fd[1]);

    waitpid(id1, NULL, 0);
    waitpid(id2, NULL, 0);
}

int main(int ac, char *av[], char **env)
{
    int pipe_index = find_pipe_index(ac, av);
    
    av[pipe_index] = NULL;
    char **cmd1 = &av[1];
    char **cmd2 = &av[pipe_index + 1];

    pipe_and_execute(cmd1, cmd2, env);

    return 0;
}