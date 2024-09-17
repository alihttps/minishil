#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "builtins.h"

#define MAX_COMMAND_LENGTH 1024

void execute_command(const char *command, char **env) 
{
    t_env *envv;
    if (strcmp(command, "env") == 0)
    {
        envv = make_env(env);
        my_env(envv);
    }
}

int main(int ac, char **av, char **env)
{
    char *input;
    char prompt[] = "MyShell$ ";

    printf("Welcome to MyShell. Type 'exit' or 'quit' to exit.\n");

    while (1) 
    {
        input = readline(prompt);

        if (input == NULL) 
        {
            printf("\nExiting shell...\n");
            break;
        }

        if (strlen(input) > 0) 
        {
            add_history(input);

            if (strcmp(input, "exit") == 0 || strcmp(input, "quit") == 0) 
            {
                printf("Exiting shell...\n");
                free(input);
                break;
            }

            execute_command(input, env);
        }

        free(input);
    }

    clear_history();
    return 0;
}