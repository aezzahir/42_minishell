#include "../../minishell.h"
extern int	g_status;
/**
 * ft_handle_quote: Handles quoted strings
 * @input: Input string
 * @start: Pointer to start index (updated to point after the opening quote)
 * @end: Pointer to end index (updated to point to the closing quote)
 * @quote: Quote character ('\"' or '\'')
 * @return: Dynamically allocated quoted substring (NULL if error occurred)
 */

int ft_handle_quote(t_list **tokens_list, char **envp, char *input, int *start, int *end, char quote)
{
    char *token;
    char    *left;
    char    *right;
    
    // printf("in handle quotes %d\n", *start);
    token = NULL;
    left = NULL;

    if (!(*end > 1 && ft_iswhitespace(input[*end - 1])))
        left = ft_substrdup(input, start, end);
    *start = *end + 1;
    if (ft_is_special_token(ft_lstlast(*tokens_list)) == HERDOC)
    {
        right = ft_strjoin("'", left);
        free(left);
        left = right;
        right = NULL;
    }
    while (input && input[*end])
    {
        *end =*end + 1;
        if (input[*end] == quote)
        {
            right = ft_substrdup(input, start, end);
            token = ft_strjoin(left, right);
            free(left);
            free(right);
            if (quote == '"')
            {
                token = ft_handle_envar(token, envp);
                token = ft_exit_status(token);  
            }
            ft_add_token(tokens_list, token);
            *end =*end + 1;
            *start = *end;
            return (TRUE);
        }   
    }
    if (left)
        free(left);
    return (FALSE);
}