#include "../../minishell.h"

/**
 * handle_heredoc: Handles here-document redirection
 * @tokens_list: Pointer to the tokens list
 * @input: Input string
 * @end: Pointer to the end index (updated to point after the delimiter)
 */
char *ft_handle_heredoc(char *input, int *end)
{
    char *delimiter = NULL;
    char *content = NULL;
    char *line = NULL;
    int start = *end;

    while (input[*end] && !ft_iswhitespace(input[*end]))
        (*end)++;

    delimiter = ft_substrdup(input, &start, end);

    content = ft_strdup("");

    while (1)
    {
        line = readline("> ");
        if (!line || !ft_strncmp(line, delimiter, ft_strlen(delimiter)))
            break;
        content = ft_strjoin(content, line);
        content = ft_strjoin(content, "\n");
        free(line);
    }

    free(delimiter);
    return content;
}