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
    char *var_name, *var_value, *left, *right, *new_token = NULL;
    
    if (!token)
        return NULL;
    (void)envp;
    while (token[i]) {
        if (token[i] == '$' && (token[i + 1] == '$' || token[i + 1] == '?')) {
            if (token[i + 1] == '?') {
                var_value = ft_itoa(g_status);
                start = i + 2;
            } else {
                i++;
                continue;
            }
        } else if (token[i] == '$' && token[i + 1] && (ft_isalnum(token[i + 1]))) {
            start = i + 1;
            while (ft_isalnum(token[start]))
                start++;
            var_name = ft_substr(token, i + 1, start - i - 1);
            var_value = getenv(var_name);
            var_value = remove_multiple_whitespaces(var_value);
            free(var_name);
        } else {
            i++;
            continue;
        }
        left = ft_substr(token, 0, i);
        right = ft_substr(token, start, ft_strlen(token) - start);
        new_token = ft_strjoin(left, var_value);
        new_token = ft_strjoin(new_token, right);
        free(left);
        free(right);
        free(token);
        token = new_token;
        i = 0;
        free(var_value);
    }
    return token;
}