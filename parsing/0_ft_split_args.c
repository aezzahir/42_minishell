#include "../minishell.h"
#include <string.h> 
/**
 * ft_split_args: Splits the input string into an array of character pointers,
 * each pointing to a separate token (command, argument, operator)
 * @cmd_line: Command line
 * @return: Array of tokens
*/

char **ft_split_quotes(char *cmd_line);
void ft_split_args(char *cmd_line)
{
    ft_split_quotes(cmd_line);
}



char **ft_split_quote(char *cmd_line)
{
    char **tokens;
    int start;
    int end;
    int i;
    
}