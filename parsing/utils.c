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


int ft_token_type(char *token_content)
{

    if (ft_strncmp(token_content, "|", 2) == 0)
        return (TOKEN_PIPE);
    else if (ft_strncmp(token_content, "<>", 3) == 0)
        return (TOKEN_IGNORE);
    else if (ft_strncmp(token_content, ">>", 3) == 0)
        return (TOKEN_APPEND);
    else if (ft_strncmp(token_content, "<<", 3) == 0)
        return (TOKEN_HEREDOC);
    else if (ft_strncmp(token_content, "<", 2) == 0)
        return (TOKEN_REDIRECT_IN);
    else if (ft_strncmp(token_content, ">", 2) == 0)
        return (TOKEN_REDIRECT_OUT);
    else
        return (TOKEN_WORD);
}

int ft_is_special_char(char c)
{
    return (c == '>' || c == '<' || c == '|');
}

int ft_is_file(t_token *token)
{
    return (token && (token->type == TOKEN_REDIRECT_IN
    || token->type == TOKEN_REDIRECT_OUT
    || token->type == TOKEN_IGNORE
    || token->type == TOKEN_HEREDOC
    || token->type == TOKEN_APPEND));
}


char *remove_quotes(char *delim)
{
    int i;
    int f;

    i = 0;
    f = 0;
    if (!delim)
        return (NULL);
    while (delim[i] && (delim[i] == '"' || delim[i] == '\''))
        i++;
    f = i;
    while (delim[f] && delim[f] && !(delim[f] == '"' || delim[f] == '\''))
        f++;
    return (ft_strndup(&delim[i], &delim[f] - &delim[i]));
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