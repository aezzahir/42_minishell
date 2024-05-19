#include "../../minishell.h"
extern int	g_status;


int ft_handle_syntax_errors(char *input)
{
    int i;
    int single_quote;
    int double_quote;

    i = 0;
    single_quote = 0;
    double_quote = 0;
    while (input[i])
    {
        if (input[i] == '\'')
            single_quote = !single_quote;
        else if (input[i] == '\"')
            double_quote = !double_quote;
        else if (input[i] == '|' && !single_quote && !double_quote)
        {
            if (i == 0 || input[i - 1] == '|' || input[i + 1] == '\0' || input[i + 1] == '|')
            {
                printf("minishell: syntax error near unexpected token `|'\n");
                return (1);
            }
        }
        else if ((input[i] == '<' || input[i] == '>') && !single_quote && !double_quote)
        {
            if ((i > 0 && input[i - 1] == '<') || (input[i + 1] && input[i + 1] == '<'))
            {
                printf("minishell: syntax error near unexpected token `<'\n");
                return (1);
            }
            else if ((i > 0 && input[i - 1] == '>') || (input[i + 1] && input[i + 1] == '>'))
            {
                printf("minishell: syntax error near unexpected token `>'\n");
                return (1);
            }
            else if (input[i + 1] == '\0' || ft_iswhitespace(input[i + 1]))
            {
                printf("minishell: syntax error near unexpected token `newline'\n");
                return (1);
            }
        }
        i++;
    }
    if (single_quote || double_quote)
    {
        printf("minishell: unclosed quotes\n");
        return (1);
    }
    return (0);
}