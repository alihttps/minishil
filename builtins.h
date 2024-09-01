#ifndef BUILTINS_H
#define BUILTINS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>

typedef struct s_env
{
    char *variable;
    char *value;
    struct s_env *next;
} t_env;


//utils
int list_len(t_env *env);
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlen(char *str);
void print_env(t_env *env);
t_env *make_env(char **env);
char *ft_strchr(char *str, int c);
char *ft_strndup (char *str, size_t n);
//my_env
void my_env(t_env *env);

#endif