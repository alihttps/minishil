#include "builtins.h"

int list_len(t_env *env)
{
    int len = 0;
    while (env)
    {
        env = env->next;
        len++;
    }
    return len;
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char *ft_strchr(char *str, int c)
{
    while (*str != '\0')
    {
        if (*str == (char)c)
            return str;
        str++;
    }
    if (c == '\0')
        return str;
    return NULL;
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	str_len;
	char	*result;
	char	*result_start;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str_len = ft_strlen(s1) + ft_strlen(s2);
	result = (char *)malloc(str_len + 1);
	if (!result)
		return (NULL);
	result_start = result;
	while (*s1)
	{
		*result = *s1;
		result++;
		s1++;
	}
	while (*s2)
	{
		*result = *s2;
		result++;
		s2++;
	}
	*result = '\0';
	return (result_start);
}

char *ft_strndup (char *str, size_t n)
{
	char *res;
	size_t len = 0;

	while (len < n && str[len] != '\0')
		len++;
	res = malloc(len + 1);
	if (!res)
		return NULL;
	int i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return res;
}

char *ft_strdup (char *str)
{
	char *res;
	size_t len = ft_strlen(str);

	res = malloc(len + 1);
	if (!res)
		return NULL;
	int i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return res;
}

void add_back(t_env **envir, t_env *var)
{
    t_env *last = get_last(*envir);
    if (!*envir)
    {
        *envir = var;
        var->prev = NULL;
    }
    else
    {
        last->next = var;
        var->prev = last;
    }
    var->next = NULL;
}

t_env *get_last(t_env *envir)
{
    if (!envir)
        return NULL;
    while(envir->next)
        envir = envir->next;
    return envir;
}