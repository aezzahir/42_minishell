#include "../../minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void ft_free(void *ptr)
{
    if (ptr)
    {
        free(ptr);
        ptr = NULL;
    }
}

void print_unset_error(const char *msg, const char *arg)
{
    ft_putstr_fd("unset: ", STDERR_FILENO);
    ft_putstr_fd((char *)msg, STDERR_FILENO);
    if (arg)
    {
        ft_putstr_fd(": ", STDERR_FILENO);
        ft_putendl_fd((char *)arg, STDERR_FILENO);
    }
}

void unset_env(char *var)
{
    if (var == NULL || *var == '\0' || strchr(var, '=') != NULL)
    {
        print_unset_error("invalid variable name", var);
        return;
    }

    if (unsetenv(var) != 0)
    {
        perror("unset");
    }
}

static size_t env_size(char *env)
{
    size_t i = 0;
    while (env[i] && env[i] != '=')
        i++;
    return (i);
}

static void free_node(t_mini *mini, t_env *env)
{
    if (mini->env == env && env->next == NULL)
    {
        ft_free(mini->env->value);
        mini->env->value = NULL;
        mini->env->next = NULL;
        return;
    }
    ft_free(env->value);
    ft_free(env);
}

int ft_unset(char **a, t_mini *mini)
{
    t_env *env;
    t_env *tmp;

    env = mini->env;
    if (!(a[1]))
        return (0);
    if (ft_strncmp(a[1], env->value, env_size(env->value)) == 0)
    {
        mini->env = (env->next) ? env->next : mini->env;
        free_node(mini, env);
        return (0);
    }
    while (env && env->next)
    {
        if (ft_strncmp(a[1], env->next->value, env_size(env->next->value)) == 0)
        {
            tmp = env->next->next;
            free_node(mini, env->next);
            env->next = tmp;
            return (0);
        }
        env = env->next;
    }
    return (0);
}

void execute_command(const char *cmd)
{
    if (system(cmd) == -1)
    {
        perror("system");
    }
}
