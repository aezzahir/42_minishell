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

char *ft_handle_quote(char *input, int *start, int *end, char quote)
{
    char *token;

    
    *start = *start + 1;
    *end = *start;
    token = NULL;
    while (input && input[*end])
    {
        if (input[*end] == quote)
        {
            token = ft_substrdup(input, start, end);
            *end =*end + 1;
            *start = *end;
            return (token);
        }
        else
           *end =*end + 1;
    }
    token = ft_substrdup(input, start, end);
    *end =*end + 1;
    *start = *end;
    return (token);
}