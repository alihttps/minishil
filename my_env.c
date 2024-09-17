#include "builtins.h"

t_env *make_env(char **env) 
{
    int i = 0;
    t_env *envir = NULL;
    t_env *new;
    char *delimiter;

    while (env[i]) 
    {
        new = malloc(sizeof(t_env));
        if (!new)
            return NULL;
        delimiter = strchr(env[i], '=');
        if (!delimiter) 
        {
            free(new);
            return NULL; 
        }
        new->variable = strndup(env[i], delimiter - env[i]);
        if (!new->variable) 
        {
            free(new);
            return NULL; 
        }
        new->value = strdup(delimiter + 1);
        if (!new->value)
        {
            free(new->variable);
            free(new);
            return NULL;
        }
        new->next = NULL;
        new->prev = NULL;
        add_back(&envir, new);
        i++;
    }
    return envir;
}

void my_env(t_env *env) 
{
    while (env) 
    {
        printf("%s=%s\n", env->variable, env->value);
        env = env->next;
    }
}

void free_env(t_env *env)
{
    t_env *temp;
    while (env)
    {
        temp = env;
        env = env->next;
        free(temp->variable);
        free(temp->value);
        free(temp);
    }
}

// int main(int argc, char **argv, char **envp)
// {
//     t_env *env = make_env(envp);
//     if (!env)
//     {
//         printf("Failed to create environment list\n");
//         return 1;
//     }

//     my_env(env);

//     free_env(env);
//     return 0;
// }