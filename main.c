#include "minishell.h"

void ft_print_nodes(void *content)
{
    printf("%s\n", (char *)content);
}

int main(int argc, char **argv, char *envp[])
{
    t_list *tokens_list;
    char *cmd_line;
    char *prompt = "mini ~$ ";

    (void)argc;
    (void)argv;
    (void)envp;
    while (TRUE)
    {
        cmd_line = readline(prompt);
        if (ft_strlen (cmd_line))
            add_history(cmd_line);
        ft_split_args(&tokens_list, cmd_line);
        ft_lstiter(tokens_list, ft_print_nodes);
        ft_parse_cmds(&tokens_list);
        ft_lstclear(&tokens_list, free);
    }
    return (0);
}