#include "../../minishell.h"
extern int	g_status;

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
    char *var_value;
    char *left;
    char *right;
    char *new_token = NULL;
    (void)envp;
    if (!token)
        return NULL;

    while (token[i]) {
        if (token[i] == '$' && token[i + 1] == '$')
        {
            i++;
            continue;
        }
        if (token[i] == '$' && token[i + 1] && token[i + 1] != '?')
        {
            start = i + 1;
            end = start;
            while (ft_isalnum(token[end]))
                end++;
            i = end - 1;

            var_name = ft_substr(token, start, end - start);
            var_value = getenv(var_name);
            var_value = remove_multiple_whitespaces(var_value);
            free(var_name);

            
            left = ft_substr(token, 0, start - 1);
            right = ft_substr(token, end, ft_strlen(token) - end);
            new_token = ft_strjoin(left, var_value);
            new_token = ft_strjoin(new_token, right);
            free(left);
            free(right);
            free(token);
            token = new_token;
        } 
        i++;
    }

    return token;
}

char *ft_exit_status(char *token)
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
        if (token[i] == '$' && token[i + 1] == '$')
        {
            i++;
            continue;
        }
        if (token[i] == '$' && token[i + 1] && token[i + 1] == '?')
        {
            start = i;
            end = i + 2;

            left = ft_substr(token, 0, start);
            right = ft_substr(token, end, ft_strlen(token) - end);
            
            char *exit_status = ft_itoa(g_status);
            new_token = ft_strjoin(left, exit_status);
            new_token = ft_strjoin(new_token, right);
            free(left);
            free(right);
            free(token);
            token = new_token;
            i = start + ft_strlen(exit_status);
            free(exit_status);
        }
        i++;   
    }

    return token;
}