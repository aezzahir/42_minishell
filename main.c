#include "minishell.h"

void ft_print_nodes(void *content)
{
    printf("%s\n", (char *)content);
}

void ft_print_prompt(t_prompt *prompt)
{
    t_cmd *cmd;
    t_list *node;
    int i;
   node = prompt->cmds;
   while (node)
   {
    i = 0;
    cmd = (t_cmd *)(node->content);
    while (cmd->cmd_args[i])
    {
        printf("%s - ", cmd->cmd_args[i]);
        i++;
    }
    node = node->next;
   }
   
}

int main(int argc, char **argv, char *envp[])
{
    t_list *tokens_list;
    t_prompt prompt;
    char *cmd_line;
    char *prompt_str = "mini ~$ ";

    (void)argc;
    (void)argv;
    (void)envp;
    while (TRUE)
    {
        cmd_line = readline(prompt_str);
        if (ft_strlen (cmd_line))
            add_history(cmd_line);
        ft_split_args(&tokens_list, cmd_line);
        ft_lstiter(tokens_list, ft_print_nodes);
        ft_parse_cmds(&prompt, &tokens_list);
        //ft_lstclear(&tokens_list, free);
    }
    return (0);
}