#include "builtins.h"

t_env *get_last(t_env *envir)
{
    if (!envir)
        return NULL;
    while(envir->next)
        envir = envir->next;
    return envir;
}

void add_back(t_env **envir, t_env *var)
{
    t_env *last = get_last(*envir);
    if (!*envir)
    {
        *envir = var;
        return;
    }
    last->next = var;
}

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
        delimiter = ft_strchr(env[i], '=');
        if (!delimiter) 
        {
            free(new);
            return NULL; 
        }
        new->variable = ft_strndup(env[i], delimiter - env[i]);
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
        add_back(&envir, new);
        i++;
    }
    return envir;
}

void my_env(t_env *env) 
{
    while (env) 
    {
        printf("%s=", env->variable);
		printf("%s\n", env->value);
        env = env->next;
    }
}

// int main (int ac, char **av, char **env)
// {
//     t_env *test = make_env(env);
//     my_env (test);
// }