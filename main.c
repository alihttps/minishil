#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "builtins.h"

#define MAX_COMMAND_LENGTH 1024

// void execute_command(t_execution *exec) 
// {
//     char **spl = ft_split(exec->input, ' ');


//     if (strcmp(spl[0], "cd") == 0)
//     {
//         my_cd(exec);
//     }
//     if (strcmp(spl[0], "export") == 0)
//     {
//         my_export(&envv, av + 1);
//         my_env(envv);
//     }
// }

int main(int ac, char **av, char **env)
{
    char *input;
    char prompt[] = "MyShell$ ";

    printf("Welcome to MyShell. Type 'exit' or 'quit' to exit.\n");

    t_execution *exec;

    exec = malloc(sizeof(t_execution));
    exec->ac = ac;
    exec->env_orginal = env;
    exec->av = av;

    make_env(exec);

    while (1) 
    {
        exec->input = readline(prompt);

        if (exec->input == NULL) 
        {
            printf("\nExiting shell...\n");
            break;
        }

        if (strlen(exec->input) > 0) 
        {
            add_history(exec->input);

            if (strcmp(exec->input, "exit") == 0 || strcmp(exec->input, "quit") == 0) 
            {
                printf("Exiting shell...\n");
                free(exec->input);
                break;
            }

            execute_command(exec);
        }

        free(exec->input);
    }

    clear_history();
    return 0;
}