#include "../../minishell.h"
extern int	g_status;

/**
 * ft_handle_quote: Handles quoted strings
 * @tokens_list: List of tokens
 * @envp: Environment variables
 * @input: Input string
 * @start: Pointer to start index (updated to point after the opening quote)
 * @end: Pointer to end index (updated to point to the closing quote)
 * @quote: Quote character ('\"' or '\'')
 * @return: TRUE if successful, FALSE otherwise
 */
int ft_handle_quote(t_list **tokens_list, char **envp, char *input, int *start, int *end, char quote)
{
    char    *left;
    char    *right;
    int     in_quote;

    left = NULL;
    right = NULL;
    in_quote = TRUE;

    left = ft_substrdup(input, start, end);
    *end = *end + 1;
    *start = *end;

    while (input[*end])
    {
        if (in_quote && input[*end] == quote)
        {
            right = ft_substrdup(input, start, end);
            left = ft_strjoin(left, right);
            free(right);
            in_quote = FALSE;
            *start = *end + 1;

            if (quote == '"')
            {
                left = ft_handle_envar(left, envp);
                left = ft_exit_status(left);
            }
        }
        else if (!in_quote && (input[*end] == '"' || input[*end] == '\''))
        {
            quote = input[*end];
            in_quote = TRUE;
            *start = *end + 1;
        }
        else if (!input[*end + 1] || (!in_quote && ft_iswhitespace(input[*end + 1])))
        {
            *end = *end + 1;
            right = ft_substrdup(input, start, end);
            left = ft_strjoin(left, right);
            free(right);
            *start = *end;
            ft_add_token(tokens_list, left);
            return (TRUE);
        }

        *end = *end + 1;
    }

    if (left)
        ft_add_token(tokens_list, left);

    return (TRUE);
}