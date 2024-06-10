#include "../minishell.h"
extern int	g_status;
int ft_iswhitespace(char c)
{
    // Check if the character is a space, tab, newline, carriage return,
    // vertical tab, or form feed
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f')
        return 1; // Return 1 (true) if it is a whitespace character
    else
        return 0; // Return 0 (false) if it is not a whitespace character
}


int ft_is_special_token(t_list *token)
{
    char *token_content;

    if (!token)
        return (-1);
    token_content = (char *)(token->content);
    if (!token_content)
        return (EMPTY);
    else if (ft_strncmp(token_content, "|", 2) == 0)
        return (PIPE);
    else if (ft_strncmp(token_content, "<>", 3) == 0)
        return (IGNORE);
    else if (ft_strncmp(token_content, ">>", 3) == 0)
        return (APPEND);
    else if (ft_strncmp(token_content, "<<", 3) == 0)
        return (HERDOC);
    else if (ft_strncmp(token_content, "<", 2) == 0)
        return (INFILE);
    else if (ft_strncmp(token_content, ">", 2) == 0)
        return (TRUNC);
    else
        return (NORMAL);
}
int ft_is_special_char(char c)
{
    return (c == '>' || c == '<' || c == '|');
}

int ft_special_token_is_a_file(t_list *token)
{
    return (ft_is_special_token(token) == INFILE
    || ft_is_special_token(token) == TRUNC
    || ft_is_special_token(token) == IGNORE
    || ft_is_special_token(token) == HERDOC
    || ft_is_special_token(token) == APPEND);
}

char *remove_quotes(char *delim)
{
    int i;

    i = 0;
    if (!delim)
        return (NULL);
    while (delim[i])
    {
        if (delim[i] == '$' && (delim[i + 1] == '"' || delim[i + 1] == '\''))
            ft_memcpy(&delim[i], &delim[i + 1], ft_strlen(&delim[i + 1]) + 1);
        if (delim[i] == '"' || delim[i] == '\'')
            ft_memcpy(&delim[i], &delim[i + 1], ft_strlen(&delim[i + 1]) + 1);
        i++;
    }
    return (delim);
}

char *remove_multiple_whitespaces(char *str)
{
    int i;
    int j;
    int len;
    char *result;

    if (str == NULL)
        return (NULL);

    len = strlen(str);
    result = (char *)malloc(sizeof(char) * (len + 1));
    if (result == NULL)
        return (NULL);

    i = 0;
    j = 0;
    while (str[i])
    {
        if (!ft_iswhitespace(str[i]))
        {
            result[j++] = str[i];
        }
        else if (j > 0 && !ft_iswhitespace(result[j - 1]))
        {
            result[j++] = ' ';
        }
        i++;
    }
    result[j] = '\0';

    if (j > 0 && ft_iswhitespace(result[j - 1]))
    {
        result[j - 1] = '\0';
    }

    return (result);
}