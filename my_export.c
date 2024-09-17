#include "builtins.h"


void swap(char **s1, char **s2)
{
    char *tmp;
    tmp = *s1;
    *s1 = *s2;
    *s2 = tmp;
}

char **sort_strings(char **str, int len) 
{
    int i = 0;
    int j;
    while (i < len - 1) 
    { 
        j = i + 1;
        while (j < len) 
        {
            if (strcmp(str[i], str[j]) > 0) 
            {
                swap(&str[i], &str[j]);
            }
            j++;
        }
        i++;
    }
    return str;
}

t_env *find_env_variable (t_env *env, char *varname)
{
    while (env)
    {
        if (strcmp(env->variable, varname) == 0)
        {
            return env;
        }
        env = env->next;
    }
    return NULL;
}

t_env *creat_env_var (char *varname, char *value)
{
    t_env *new_var = malloc(sizeof(t_env));

    new_var->variable = varname;
    new_var->value = value;
    new_var->next = NULL;
    new_var->prev = NULL;

    return new_var;
}

int my_export(t_env **env, char **args)
{
    int i = 0;
    while (args[i])
    {
        char *arg = args[i];
        char *equal = strchr(arg, '=');
        char *plus = strchr(arg, '+');

        t_env *existing;
        t_env *new_var;

        if (!equal)
        {
            existing = find_env_variable(*env, arg);
            if (!existing)
            {
                new_var = creat_env_var(arg, "");
                if (!new_var)
                    return 1; 
                add_back(env, new_var);
                printf("Exported: %s\n", arg);
            }
            else
                printf("Already exported: %s\n", arg);
        }
        else
        {
            int is_append = (plus && plus + 1 == equal);
            int name_len;

            if (is_append)
                name_len = plus - arg;
            else
                name_len = equal - arg;

            char *var_name = malloc(name_len + 1);
            if (!var_name)
                return 1; 
            strncpy(var_name, arg, name_len);
            var_name[name_len] = '\0';

            char *value = equal + 1;

            existing = find_env_variable(*env, var_name);

            if (existing)
            {
                if (is_append)
                {
                    char *new_value = ft_strjoin(existing->value, value);
                    if (!new_value)
                    {
                        free(var_name);
                        return 1;
                    }
                    free(existing->value);
                    existing->value = new_value;
                }
                else
                {
                    char *new_value = ft_strdup(value);
                    if (!new_value)
                    {
                        free(var_name);
                        return 1;
                    }
                    free(existing->value);
                    existing->value = new_value;
                }
                printf("Updated: %s=%s\n", var_name, existing->value);
            }
            else
            {
                new_var = creat_env_var(var_name, value);
                if (!new_var)
                {
                    free(var_name);
                    return 1;
                }
                add_back(env, new_var);
                printf("Exported: %s=%s\n", var_name, value);
            }
        }
        i++;
    }

    return 0;
}


int main(int ac, char **av, char **env)
{
    t_env *envir = make_env(env);

    int result = my_export(&envir, av + 1);
    if (result != 0)
    {
        printf("Export failed\n");
        return 1;
    }
    my_env(envir);
    return 0;
}