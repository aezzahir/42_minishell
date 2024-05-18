#include "../../minishell.h"


/**
 * ft_handle_envar: Replaces environment variable names with their values
 * @token: Token (string) to handle
 * @envp: Environment variables array
 * @return: Token with environment variables replaced
 */

char *ft_handle_envar(char *token, char **envp)
{
    int i = 0;
    int start = 0;
    int end = 0;
    char *var_name;
    char *left;
    char *right;
    char *new_token = NULL;

    if (!token)
        return NULL;

    while (token[i]) {
        if (token[i] == '$')
        {
            start = i + 1;
            end = start;
            while (ft_isalnum(token[end]))
                end++;
            i = end - 1;

            var_name = ft_substr(token, start, end - start);
            char *var_value = getenv(var_name);
            free(var_name);

            if (var_value) {
                left = ft_substr(token, 0, start - 1);
                right = ft_substr(token, end, ft_strlen(token) - end);
                new_token = ft_strjoin(left, var_value);
                new_token = ft_strjoin(new_token, right);
                free(left);
                free(right);
                free(token);
                token = new_token;
            }
        } 
        else {
            i++;
        }
    }

    return token;
}

char *ft_exit_status(char *token, int *g_status)
{
    int i = 0;
    int start = 0;
    int end = 0;
    char *left;
    char *right;
    char *new_token = NULL;

    if (!token)
        return NULL;

    while (token[i])
    {
        if (token[i] == '$' && token[i + 1] == '?')
        {
            start = i;
            end = i + 2;

            left = ft_substr(token, 0, start);
            right = ft_substr(token, end, ft_strlen(token) - end);
            
            char *exit_status = ft_itoa(*g_status);
            new_token = ft_strjoin(left, exit_status);
            new_token = ft_strjoin(new_token, right);

            free(left);
            free(right);
            free(exit_status);
            free(token);

            token = new_token;
            i = start + ft_strlen(exit_status);
        }
        else
        {
            i++;
        }
    }

    return token;
}