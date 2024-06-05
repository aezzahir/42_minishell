#include "../../minishell.h"
extern int	g_status;
/**
 * handle_heredoc: Handles here-document redirection
 * @tokens_list: Pointer to the tokens list
 * @input: Input string
 * @end: Pointer to the end index (updated to point after the delimiter)
 */



void ft_handle_heredoc(t_list **tokens_list, char *input, int *end)
{
    char *delimiter = NULL;
    int start = *end;

    while (ft_iswhitespace(input[*end]))
        (*end)++;

    start = *end;
    while (input[*end] && !ft_iswhitespace(input[*end]))
        (*end)++;

    delimiter = ft_substrdup(input, &start, end);
    ft_add_token(tokens_list, ft_strdup("<<"));
    ft_add_token(tokens_list, delimiter);
    start = *end;
}