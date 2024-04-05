#include "../minishell.h"
#include <stdbool.h>
 #include <stdlib.h>
bool is_special_char(char c)
{
    return (c == '<' || c == '|' || c == '>');
}

/**
 * ft_split_args:  function that takes the command line
 *              and separates it by taking spaces and quotes into account.
 * @cmd_line: Command line
 * @return: Array of tokens
 */

void ft_split_args(char *cmd_line)
{
    char *token;
    bool in_quotes = false;

    while (*cmd_line)
    {
        while (*cmd_line == ' ' || (*cmd_line >= 9 && *cmd_line <= 13)) 
            cmd_line++;
        if (*cmd_line)
        {
            token = cmd_line;
            if (*cmd_line == '"' || *cmd_line == '\'')
                in_quotes = !in_quotes;
            while (*cmd_line && ((*cmd_line != ' ' && !is_special_char(*cmd_line)) || in_quotes))
            {
                if (*cmd_line == '"' || *cmd_line == '\'')
                {
                    in_quotes = !in_quotes;
                }
                cmd_line++;
            }
            if (*cmd_line && !in_quotes && is_special_char(*cmd_line))
            {
                printf("%.*s\n", (int)(cmd_line - token), token);
                printf("%c\n", *cmd_line);
                cmd_line++;
            }
            else
            {
                if (*cmd_line)
                {
                    *cmd_line = '\0';
                    cmd_line++;
                }
                if (*token == '$')
                {
                    char *var_name = token + 1;
                    char  *var_value = getenv(var_name);
                    if (var_value)
                        printf("%s\n", var_value);
                    continue;
                }
            }
            // store the token either into array or linked list
            printf("%s\n", token);
        }
    }
}
