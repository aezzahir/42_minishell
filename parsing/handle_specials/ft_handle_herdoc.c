#include "../../minishell.h"

/**
 * handle_heredoc: Handles here-document redirection
 * @tokens_list: Pointer to the tokens list
 * @input: Input string
 * @end: Pointer to the end index (updated to point after the delimiter)
 */



char *ft_handle_heredoc(char *input, int *end, char **envp, int *g_status)
{
    char *delimiter = NULL;
    char *content = NULL;
    char *line = NULL;
    int start = *end;

    while (ft_iswhitespace(input[*end]))
        (*end)++;
    start = *end;
    while (input[*end] && !ft_iswhitespace(input[*end]))
        (*end)++;

    delimiter = ft_substrdup(input, &start, end);

    content = ft_strdup("");
    while (1)
    {
        line = readline("heredoc> ");
        if (!line)
            break;
        if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
        {
            free(line);
            break;
        }
        line = ft_handle_envar(line, envp);
        line = ft_exit_status(line, g_status);
        content = ft_strjoin(content, line);
        content = ft_strjoin(content, "\n");
        free(line);
    }
    free(delimiter);
    content = ft_handle_envar(content, envp);
    content = ft_exit_status(content, g_status);
    return content;
}