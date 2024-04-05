#include "../minishell.h"
#include <string.h> 
/**
 * ft_split_args: Splits the input string into an array of character pointers,
 * each pointing to a separate token (command, argument, operator)
 * @cmd_line: Command line
 * @return: Array of tokens
*/
char *ft_handle_dquote(char *input, int *start, int *end)
{
    char *token;

    *end = *start +1;
    while (input && input[*end])
    {
        if (input[*end] == '"')
        {
            *end =*end + 1;
            token = ft_substrdup(input, start, end);
            printf("%s\n", token);
            *start = *end;
            return (token);
        }
        else
           *end =*end + 1;
    }
    *end = *start;
    token = input;
    input = ft_strjoin(input, readline("dquote>"));
    free(token);
    ft_handle_dquote(input, start, end);
    return(input);
}

char *ft_handle_quote(char *input, int *start, int *end)
{
    char *token;

    *end = *start + 1;
    while (input && input[*end])
    {
        if (input[*end] == '\'')
        {
            *end =*end + 1;
            token = ft_substrdup(input, start, end);
            printf("%s\n", token);
            *start = *end;
            return (token);
        }
        else
           *end =*end + 1;
    }
    *end = *start;
    token = input;
    input = ft_strjoin(input, readline("quote>"));
    free(token);
    ft_handle_dquote(input, start, end);
    return(input);
}
void ft_split_args(char *input)
{
    char *token;
    int start = 0;
    int end = 0;

    while (input && input[end])
    {
        if (input[end] == ' ')
        {
            if (end > start)
            {
                token = ft_substrdup(input, &start, &end);
                printf("%s\n", token);
            }
            end++;
            start = end;
        }
        else if (input[end] == '"' && input[end - 1] == ' ') // check input[end - 1] accessbility and it is a space;
        {
            token = ft_handle_dquote(input, &start, &end);  
        }
        else if (input[end] == '\'' && (end == 0 || input[end - 1] == ' ')) // check input[end - 1] accessbility and it is a space;
        {
            token = ft_handle_quote(input, &start, &end);  
        }
        else if (!ft_strncmp(&input[end], ">>", 2) || !ft_strncmp(&input[end], "<<", 2))
        {
            end = end + 2;
            token = ft_substrdup(input, &start, &end);
            printf("%s\n", token);
            start = end;
        }
        else if (input[end] == '|' || input[end] == '>' || input[end] == '<')
        {
            end = end + 1;
            token = ft_substrdup(input, &start, &end);
            printf("%s\n", token);
            start = end;
        }
        else
            end++;
        //printf("start = %d; end = %d\n", start, end);
    }
    token = ft_substrdup(input, &start, &end);
    printf("%s\n", token);
}