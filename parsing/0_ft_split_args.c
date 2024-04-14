#include "../minishell.h"
#include <string.h> 
/**
 * ft_split_args: Splits the input string into an array of character pointers,
 * each pointing to a separate token (command, argument, operator)
 * @cmd_line: Command line
 * @return: Array of tokens
 * 
 * 
*/
char *ft_handle_envar(char *token)
{
    int     i = 0;
    int     start = 0;
    int     end = 0;
    char    *var_name;
    char    *left;
    char    *right;
    var_name = NULL;

    while (token && token[i])
    {
        if (token[i] == '$')
        {
            start = i + 1;
            end = i + 1;
            while (ft_isalnum(token[end]))
            {
                end++;
            }
            i = end - 1;
            if (1)
            {
                var_name = ft_substr(token, start, end - start); //
                var_name = getenv(var_name);
                left = ft_strjoin(ft_substr(token, 0, start - 1), var_name);
                right = ft_strjoin(left, ft_substr(token, end, ft_strlen(token) - end));
                free(token);
                free(left);
                token = right;
                return (token);
            }
        }
        i++;
    }
    return (token);
}
char *ft_handle_dquote(char *input, int *start, int *end)
{
    char *token;

    *end = *start + 1;
    token = NULL;
    while (input && input[*end])
    {
        if (input[*end] == '"')
        {
            *end =*end + 1;
            token = ft_substrdup(input, start, end);
        
            *start = *end;
            return (token);
        }
        else
           *end =*end + 1;
    }
//    //*end = *start;
//     token = input;
//     input = ft_strjoin(input, "\n");
//     free(token);
//     token = input;
//     input = ft_strjoin(input, readline("dquote>"));
//     free(token);
//     ft_handle_dquote(input, start, end);
    return(token);
}

char *ft_handle_quote(char *input, int *start, int *end)
{
    char *token;

    *end = *start + 1;
    token = NULL;
    while (input && input[*end])
    {
        if (input[*end] == '\'')
        {
            *end =*end + 1;
            token = ft_substrdup(input, start, end);
            *start = *end;
            return (token);
        }
        else
           *end =*end + 1;
    }
    return(token);
}



void ft_add_token(t_list **tokens_list, char *token)
{
    ft_lstadd_back(tokens_list, ft_lstnew((void *)token));
    
}


void ft_split_args(t_list **tokens_list, char *input)
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
                token = ft_handle_envar(token);//to be updated 1111
                ft_add_token(tokens_list, token);
            }
            end++;
            start = end;
        }
        else if (input[end] == '"' && (end == 0 || (end > 0 && input[end - 1] == ' '))) // check input[end - 1] accessbility and it is a space;
        {
            token = ft_handle_dquote(input, &start, &end);
            token = ft_handle_envar(token);//to be updated 1111
            ft_add_token(tokens_list, token); 
        }
        else if (input[end] == '\'' && (end == 0 || (end > 0 && input[end - 1] == ' '))) // check input[end - 1] accessbility and it is a space;
        {
            token = ft_handle_quote(input, &start, &end);
            //token = ft_handle_envar(token);//to be updated  1111
            ft_add_token(tokens_list, token);
        }
        else if (!ft_strncmp(&input[end], ">>", 2) || !ft_strncmp(&input[end], "<<", 2))
        {
            end = end + 2;
            token = ft_substrdup(input, &start, &end);
            start = end;
            token = ft_handle_envar(token);//to be updated  ---1111
            ft_add_token(tokens_list, token);
        }
        else if (input[end] == '|' || input[end] == '>' || input[end] == '<')
        {
            end = end + 1;
            token = ft_substrdup(input, &start, &end);
            start = end;
            token = ft_handle_envar(token);//to be updated  ---1111
            ft_add_token(tokens_list, token);
        }
        else
            end++;
    }
    token = ft_substrdup(input, &start, &end);
    token = ft_handle_envar(token);//to be updated  ---1111
    ft_add_token(tokens_list, token);
}