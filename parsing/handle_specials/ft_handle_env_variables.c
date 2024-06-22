#include "../../minishell.h"
extern int	g_status;

/**
 * ft_handle_envar: Replaces environment variable names with their values
 * @token: Token (string) to handle
 * @envp: Environment variables array
 * @return: Token with environment variables replaced
 */
char *ft_strjoin_free(char *s1, char *s2)
{
    size_t len1 = ft_strlen(s1);
    size_t len2 = ft_strlen(s2);
    char *result = malloc(len1 + len2 + 1);
    if (result == NULL)
        return NULL;
    ft_memcpy(result, s1, len1);
    ft_memcpy(result + len1, s2, len2 + 1);
    free(s1);
    return result;
}

void ft_expand_variables(t_list *tokens_list, char **envp)
{
    t_list *current = tokens_list;
    while (current != NULL) {
        t_token *token = (t_token *)current->content;
        if (token->type == TOKEN_WORD && strchr(token->value, '$') != NULL) {
            char *expanded_value = ft_expand_variable(token->value, envp);
            free(token->value);
            token->value = expanded_value;
        }
        current = current->next;
    }
}


char *ft_getenv(char *var_name, char **envp)
{
    int i = 0;
    int var_len = ft_strlen(var_name);

    while (envp[i])
    {
        if (ft_strncmp(envp[i], var_name, var_len) == 0 && envp[i][var_len] == '=')
            return envp[i] + var_len + 1;
        i++;
    }
    return NULL;
}

char *ft_expand_variable(char *token, char **envp)
{
    int i = 0;
    int single_quote = 0;
    int double_quote = 0;
    char *expanded_token = ft_strdup("");

    while (token[i])
    {
        if (token[i] == '\'' && !double_quote)
        {
            single_quote = !single_quote;
            char *temp = ft_substr(token, i, 1);
            expanded_token = ft_strjoin_free(expanded_token, temp);
            free(temp);
            expanded_token = ft_strjoin_free(expanded_token, "\'");
            i++;
        }
        else if (token[i] == '"' && !single_quote)
        {
            double_quote = !double_quote;
            expanded_token = ft_strjoin_free(expanded_token, "\"");
            i++;
        }
        else if (token[i] == '$' && !single_quote)
        {
            if (token[i + 1] == '?')
            {
                char *exit_status = ft_itoa(g_status);
                expanded_token = ft_strjoin_free(expanded_token, exit_status);
                free(exit_status);
                i += 2;
            }
            else if (ft_isalpha(token[i + 1]) || token[i + 1] == '_')
            {
                int k = i + 1;
                while (ft_isalnum(token[k]) || token[k] == '_')
                    k++;
                char *var_name = ft_substr(token, i + 1, k - i - 1);
                char *var_value = ft_getenv(var_name, envp);
                if (var_value)
                    expanded_token = ft_strjoin_free(expanded_token, var_value);
                free(var_name);
                i = k;
            }
            else if (ft_isdigit(token[i + 1]))
                i += 2;
            else if (token[i + 1] == '"' || token[i + 1] == '\'')
                i += 1;
            else
            {
                char *temp = ft_substr(token, i, 1);
                expanded_token = ft_strjoin_free(expanded_token, temp);
                free(temp);
                i++;
            }
        }
        else
        {
            char *temp = ft_substr(token, i, 1);
            expanded_token = ft_strjoin_free(expanded_token, temp);
            free(temp);
            i++;
        }
    }
    return expanded_token;
}
