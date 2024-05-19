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