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
    else if (ft_strncmp(token_content, "<", 2) == 0)
        return (INFILE);
    else if (ft_strncmp(token_content, ">", 2) == 0)
        return (TRUNC);
    else if (ft_strncmp(token_content, ">>", 3) == 0)
        return (APPEND);
    else if (ft_strncmp(token_content, "<<", 3) == 0)
        return (HERDOC);
    else
        return (NORMAL);
}


int ft_special_token_is_a_file(t_list *token)
{
    return (ft_is_special_token(token) == INFILE
    || ft_is_special_token(token) == TRUNC
    || ft_is_special_token(token) == APPEND);
}